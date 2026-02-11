print(raw_ostream &OS, const Module *) const {
    OS << "CallGraph Root is: ";
    if (Function *F = getRoot()->getFunction())
      OS << F->getName() << "\n";
    else {
      OS << "<<null function: 0x" << getRoot() << ">>\n";
    }

    CallGraph::print(OS, 0);
  }
