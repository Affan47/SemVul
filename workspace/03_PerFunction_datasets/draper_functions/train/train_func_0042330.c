flushPendingLabels(MCFragment *F, uint64_t FOffset) {
  if (PendingLabels.empty())
    return;
  if (!F) {
    F = new MCDataFragment();
    MCSection *CurSection = getCurrentSectionOnly();
    CurSection->getFragmentList().insert(CurInsertionPoint, F);
    F->setParent(CurSection);
  }
  for (MCSymbol *Sym : PendingLabels) {
    Sym->setFragment(F);
    Sym->setOffset(FOffset);
  }
  PendingLabels.clear();
}
