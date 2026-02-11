DumpNodes(const SDNode *N, unsigned indent, const SelectionDAG *G) {
  for (unsigned i = 0, e = N->getNumOperands(); i != e; ++i)
    if (N->getOperand(i).getNode()->hasOneUse())
      DumpNodes(N->getOperand(i).getNode(), indent+2, G);
    else
      dbgs() << "\n" << std::string(indent+2, ' ')
           << (void*)N->getOperand(i).getNode() << ": <multiple use>";


  dbgs() << "\n";
  dbgs().indent(indent);
  N->dump(G);
}
