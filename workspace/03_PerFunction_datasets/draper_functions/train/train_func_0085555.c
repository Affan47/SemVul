print(raw_ostream &OS, const Module *M) const {
  OS << "IV Users for loop ";
  WriteAsOperand(OS, L->getHeader(), false);
  if (SE->hasLoopInvariantBackedgeTakenCount(L)) {
    OS << " with backedge-taken count "
       << *SE->getBackedgeTakenCount(L);
  }
  OS << ":\n";

  for (ilist<IVStrideUse>::const_iterator UI = IVUses.begin(),
       E = IVUses.end(); UI != E; ++UI) {
    OS << "  ";
    WriteAsOperand(OS, UI->getOperandValToReplace(), false);
    OS << " = " << *getReplacementExpr(*UI);
    for (PostIncLoopSet::const_iterator
         I = UI->PostIncLoops.begin(),
         E = UI->PostIncLoops.end(); I != E; ++I) {
      OS << " (post-inc with loop ";
      WriteAsOperand(OS, (*I)->getHeader(), false);
      OS << ")";
    }
    OS << " in  ";
    UI->getUser()->print(OS);
    OS << '\n';
  }
}
