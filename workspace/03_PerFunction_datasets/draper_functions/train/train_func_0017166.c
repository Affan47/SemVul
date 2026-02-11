Print(Function &F, raw_ostream &OS) const {
  OS << "\nFUNCTION: " << F.getNameStr() << "\n";
  for (Function::iterator BB = F.begin(), E = F.end(); BB != E; ++BB) {
    if (!BBExecutable.count(BB))
      OS << "INFEASIBLE: ";
    OS << "\t";
    if (BB->hasName())
      OS << BB->getNameStr() << ":\n";
    else
      OS << "; anon bb\n";
    for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E; ++I) {
      LatticeFunc->PrintValue(getLatticeState(I), OS);
      OS << *I << "\n";
    }

    OS << "\n";
  }
}
