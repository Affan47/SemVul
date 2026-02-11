findDefinedVNInfoForRegInt(SlotIndex Idx) const {
  for (LiveInterval::const_vni_iterator i = vni_begin(), e = vni_end();
       i != e; ++i) {
    if ((*i)->def == Idx)
      return *i;
  }

  return 0;
}
