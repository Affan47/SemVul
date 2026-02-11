add(vector<Edge*> *edges, void* edgeSet)
{
	for (unsigned int i=0; i<edges->size(); ++i)
	{
		Edge *edge=(*edges)[i];
		add(edge,edgeSet);
	}
}
