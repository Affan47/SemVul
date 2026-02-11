isLiveOut(unsigned Reg) const {
  for (liveout_iterator I = liveout_begin(), E = liveout_end(); I != E; ++I)
    if (*I == Reg)
      return true;
  return false;
}
