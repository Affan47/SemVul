remove(Edge *edge)
{
	remove(edge->getDirEdge(0));
	remove(edge->getDirEdge(1));
	for(unsigned int i=0; i<edges.size();++i)
	{
		if(edges[i]==edge) {
			edges.erase(edges.begin()+i);
			--i;
		}
	}
}
