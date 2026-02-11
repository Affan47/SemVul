ComputeNamedNodes() {
  for (unsigned i = 0, e = Trees.size(); i != e; ++i)
    ComputeNamedNodes(Trees[i]);
}
