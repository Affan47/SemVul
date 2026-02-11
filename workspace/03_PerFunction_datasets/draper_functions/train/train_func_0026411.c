hasComputableLoopEvolution(const Loop *L) const {
  bool HasVarying = false;
  for (op_iterator I = op_begin(), E = op_end(); I != E; ++I) {
    const SCEV *S = *I;
    if (!S->isLoopInvariant(L)) {
      if (S->hasComputableLoopEvolution(L))
        HasVarying = true;
      else
        return false;
    }
  }
  return HasVarying;
}
