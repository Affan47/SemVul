GetSatAssumptions(vector<Theorem>& assumptions) const {
  DebugAssert(!isRefl() && !isFlagged(), "Invariant violated");
  setFlag();
  const Assumptions& a = getAssumptionsRef();
  for (Assumptions::iterator i = a.begin(); i != a.end(); i++) {
    if ((*i).isRefl() || (*i).isFlagged()) continue;
    (*i).GetSatAssumptionsRec(assumptions);
  }
}
