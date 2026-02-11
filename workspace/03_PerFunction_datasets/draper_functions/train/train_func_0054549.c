computeIntervals() {
  for (unsigned i = 0, e = userValues.size(); i != e; ++i) {
    UserValueScopes UVS(userValues[i]->getDebugLoc(), LS);
    userValues[i]->computeIntervals(MF->getRegInfo(), *TRI, *LIS, *MDT, UVS);
    userValues[i]->mapVirtRegs(this);
  }
}
