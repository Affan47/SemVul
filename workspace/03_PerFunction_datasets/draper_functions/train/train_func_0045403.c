getFixedStack(int FI) {
  PSVGlobalsTy &PG = *PSVGlobals;
  sys::ScopedLock locked(PG.Lock);
  const PseudoSourceValue *&V = PG.FSValues[FI];
  if (!V)
    V = new FixedStackPseudoSourceValue(FI);
  return V;
}
