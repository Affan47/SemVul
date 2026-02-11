CreateEmptySubgraph() {
  HSubgraph* subgraph = new HSubgraph(graph());
  subgraph->Initialize(graph()->CreateBasicBlock());
  return subgraph;
}
