DumpNodesr(raw_ostream &OS, const SDNode *N, unsigned indent,
                       const SelectionDAG *G, VisitedSDNodeSet &once) {
  if (!once.insert(N))
    return;


  OS << std::string(indent, ' ');
  N->printr(OS, G);


  for (unsigned i = 0, e = N->getNumOperands(); i != e; ++i) {
    const SDNode *child = N->getOperand(i).getNode();

    if (i) OS << ",";
    OS << " ";

    if (child->getNumOperands() == 0) {

      child->printr(OS, G);
      once.insert(child);
    } else {
      OS << (void*)child;
      if (unsigned RN = N->getOperand(i).getResNo())
        OS << ":" << RN;
    }
  }

  OS << "\n";


  for (unsigned i = 0, e = N->getNumOperands(); i != e; ++i) {
    const SDNode *child = N->getOperand(i).getNode();
    DumpNodesr(OS, child, indent+2, G, once);
  }
}
