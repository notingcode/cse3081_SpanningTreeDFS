
#include "Graph_adj_array.h"

void Read_Graph_adj_array (int Vnum, vertex V[], int Enum, edge E[]) {
	// read graph information
	// V와 E의 name field는 각각 자신의 인덱스를 저장한다
	// V[].flag과 E[].flag은 반드시 false로 설정해야 한다.
	
	int k, vf, vr, ec;
	// Initialize each vertex
	for (k = 0; k < Vnum; ++k) {
		V[k].f_hd = V[k].r_hd = NONE;
		V[k].flag = false;
		V[k].name = k;
	}
	// Attach edge index to each vertex and initialize each edge
	for (k = 0; k < Enum; ++k) {
		scanf_s("%d %d %d", &vf, &vr, &ec);
		E[k].fp = E[k].rp = NONE;
		
		if (V[vf].f_hd == NONE) {
			V[vf].f_hd = k;
		}
		else {
			E[k].fp = V[vf].f_hd;
			V[vf].f_hd = k;
		}

		if (V[vr].r_hd == NONE) {
			V[vr].r_hd = k;
		}
		else {
			E[k].rp = V[vr].r_hd;
			V[vr].r_hd = k;
		}
	
		E[k].name = k;
		E[k].flag = false;
		E[k].cost = ec;
		E[k].vf = vf;
		E[k].vr = vr;
	}
}

int DFS_Tree_adj_array(
	int     src,   // source node index
	int     Vnum,  // number of vertices
	vertex *V,     // vertex structure array (starting index 0)
	int     Enum,  // number of edges
	edge   *E     // edge structure array (starting index 0) 
) {  
	// DFS를 사용하여 DFS tree에 속하는 에지의 flag을 true로 설정한다.
	// DFS 시작 vertex는 입력 파일에서 지정된다(src).
	// DFS tree에 속한 에지의 cost 함을 return 한다(모든 각 edge cost가 1이면 unique)
	// recursive 함수로 작성해도 무방하다.
	int k, adj_v, sumCost = 0;
	// Mark current vertex(src) as visited
	V[src].flag = true;

	// Examine edges with src as front vertex
	if (V[src].f_hd != NONE) {
		k = V[src].f_hd;
		do {
			adj_v = E[k].vr;

			if (V[adj_v].flag == false) {
				E[k].flag = true;
				sumCost += E[k].cost;
				sumCost += DFS_Tree_adj_array(adj_v, Vnum, V, Enum, E);
			}
		} while ((k = E[k].fp) != NONE);
	}
	// Examine edges with src as rear vertex
	if (V[src].r_hd != NONE) {
		k = V[src].r_hd;
		do {
			adj_v = E[k].vf;

			if (V[adj_v].flag == false) {
				E[k].flag = true;
				sumCost += E[k].cost;
				sumCost += DFS_Tree_adj_array(adj_v, Vnum, V, Enum, E);
			}
		} while ((k = E[k].rp) != NONE);
	}

	return sumCost;
}
