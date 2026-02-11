deleteAllEdges(Node *node)
{
	std::vector<DirectedEdge*> &edges=node->getOutEdges()->getEdges();
	for(unsigned int i=0; i<edges.size(); ++i) {
		PolygonizeDirectedEdge *de=(PolygonizeDirectedEdge*)edges[i];
		de->setMarked(true);
		PolygonizeDirectedEdge *sym=(PolygonizeDirectedEdge*) de->getSym();
		if (sym!=NULL)
			sym->setMarked(true);
	}
}
