NextUsePositionRegisterIsBeneficial(
    LifetimePosition start) {
  UsePosition* pos = NextUsePosition(start);
  while (pos != NULL && !pos->RegisterIsBeneficial()) {
    pos = pos->next();
  }
  return pos;
}
