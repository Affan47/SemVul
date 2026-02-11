getPrimaryEdges(bool includeFrame)
{
	QuadEdgeList *edges = new QuadEdgeList();
	QuadEdgeStack edgeStack;
	QuadEdgeSet visitedEdges;

	edgeStack.push(startingEdges[0]);

	while (!edgeStack.empty())
	{
		QuadEdge *edge = edgeStack.top();
		edgeStack.pop();
		if (visitedEdges.find(edge) == visitedEdges.end())
		{
			QuadEdge* priQE = (QuadEdge*)&edge->getPrimary();

			if (includeFrame || ! isFrameEdge(*priQE))
				edges->push_back(priQE);

			edgeStack.push(&edge->oNext());
			edgeStack.push(&edge->sym().oNext());

			visitedEdges.insert(edge);
			visitedEdges.insert(&edge->sym());
		}
	}
	return std::auto_ptr<QuadEdgeList>(edges);
}
