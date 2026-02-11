toEdges(vector<DirectedEdge*>& dirEdges, vector<Edge*>& edges)
{
	for (size_t i=0, n=dirEdges.size(); i<n; ++i)
	{
		edges.push_back(dirEdges[i]->parentEdge);
	}
}
