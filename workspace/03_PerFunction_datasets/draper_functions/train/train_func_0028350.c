deleteDangles(std::vector<const LineString*>& dangleLines)
{
	std::vector<Node*> nodeStack;
	findNodesOfDegree(1, nodeStack);

	std::set<const LineString*> uniqueDangles;

	while (!nodeStack.empty()) {
		Node *node=nodeStack.back();
		nodeStack.pop_back();
		deleteAllEdges(node);
		std::vector<DirectedEdge*> &nodeOutEdges=node->getOutEdges()->getEdges();
		for(unsigned int j=0; j<nodeOutEdges.size(); ++j)
		{
			PolygonizeDirectedEdge *de=(PolygonizeDirectedEdge*)nodeOutEdges[j];

			de->setMarked(true);
			PolygonizeDirectedEdge *sym=(PolygonizeDirectedEdge*) de->getSym();
			if (sym != NULL)
				sym->setMarked(true);

			PolygonizeEdge *e=(PolygonizeEdge*) de->getEdge();
			const LineString* ls = e->getLine();
			if ( uniqueDangles.insert(ls).second )
				dangleLines.push_back(ls);
			Node *toNode=de->getToNode();


			if (getDegreeNonDeleted(toNode)==1)
				nodeStack.push_back(toNode);
		}
	}

}

}
