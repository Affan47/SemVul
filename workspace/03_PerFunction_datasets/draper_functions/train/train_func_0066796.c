getLoopName(const LoopData &Loop) const {
  return getBlockName(Loop.getHeader()) + (Loop.isIrreducible() ? "**" : "*");
}
