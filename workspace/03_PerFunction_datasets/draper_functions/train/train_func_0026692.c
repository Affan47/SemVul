CanCauseHighRegPressure(DenseMap<unsigned, int> &Cost) {
  for (DenseMap<unsigned, int>::iterator CI = Cost.begin(), CE = Cost.end();
       CI != CE; ++CI) {
    if (CI->second <= 0)
      continue;

    unsigned RCId = CI->first;
    for (unsigned i = BackTrace.size(); i != 0; --i) {
      SmallVector<unsigned, 8> &RP = BackTrace[i-1];
      if (RP[RCId] + CI->second >= RegLimit[RCId])
        return true;
    }
  }

  return false;
}
