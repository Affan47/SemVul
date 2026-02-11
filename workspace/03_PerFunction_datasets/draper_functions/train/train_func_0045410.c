verifyDomTree() const {
  Function &F = *getRoot()->getParent();

  DominatorTree OtherDT;
  OtherDT.recalculate(F);
  if (compare(OtherDT)) {
    errs() << "DominatorTree is not up to date!\nComputed:\n";
    print(errs());
    errs() << "\nActual:\n";
    OtherDT.print(errs());
    abort();
  }
}
