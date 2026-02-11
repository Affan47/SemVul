FindSubprogram(const Function *F,
                                    DebugInfoFinder &Finder) {
  for (DISubprogram *Subprogram : Finder.subprograms()) {
    if (Subprogram->describes(F))
      return Subprogram;
  }
  return nullptr;
}
