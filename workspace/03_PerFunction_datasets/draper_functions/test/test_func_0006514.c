dump() const {
  dbgs() << "SelectionDAG has " << AllNodes.size() << " nodes:";

  for (allnodes_const_iterator I = allnodes_begin(), E = allnodes_end();
       I != E; ++I) {
    const SDNode *N = I;
    if (!N->hasOneUse() && N != getRoot().getNode())
      DumpNodes(N, 2, this);
  }

  if (getRoot().getNode()) DumpNodes(getRoot().getNode(), 2, this);

  dbgs() << "\n\n";
}
