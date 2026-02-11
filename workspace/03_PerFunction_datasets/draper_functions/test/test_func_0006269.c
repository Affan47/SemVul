addEdges(Node* node,
		stack<Node *>& nodeStack, Subgraph* subgraph)
{
	node->setVisited(true);
	DirectedEdgeStar *des=node->getOutEdges();
	for (DirectedEdge::Vect::iterator i=des->begin(), iEnd=des->end();
			i!=iEnd; ++i)
	{
		DirectedEdge *de=*i;
		subgraph->add(de->getEdge());
		Node *toNode = de->getToNode();
		if ( ! toNode->isVisited() ) nodeStack.push(toNode);
	}
}
