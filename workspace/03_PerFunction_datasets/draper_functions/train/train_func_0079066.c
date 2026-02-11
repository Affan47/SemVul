getDegree(Node *node, long label)
{
	std::vector<DirectedEdge*> &edges=node->getOutEdges()->getEdges();
	int degree=0;
	for(unsigned int i=0; i<edges.size(); ++i)
	{
		PolygonizeDirectedEdge *de=(PolygonizeDirectedEdge*)edges[i];
		if (de->getLabel()==label) ++degree;
	}
	return degree;
}
