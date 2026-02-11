hasNextReloadInterval(LiveInterval *cur) {
  DenseMap<unsigned, unsigned>::iterator I = NextReloadMap.find(cur->reg);
  if (I == NextReloadMap.end())
    return 0;
  return &li_->getInterval(I->second);
}
