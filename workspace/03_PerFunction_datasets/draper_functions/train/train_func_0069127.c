findSubgraph(Node* node)
{
	Subgraph* subgraph = new Subgraph(graph);
	addReachable(node, subgraph);
	return subgraph;
}
