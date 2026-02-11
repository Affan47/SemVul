addEdge(int i, int j, int w ) {
	if(i == j) return false;
	Vertex *v = vertices[i];

	unordered_map<int, int>::iterator eit = v->edges.find(j);
	if(eit != v->edges.end())
		return false;


	v->edges[j] = w;
	vertices[j]->edges[i] = w;
	return true;
}
