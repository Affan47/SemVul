getNamedRegionTimer(StringRef Name) {
  sys::SmartScopedLock<true> L(*TimerLock);

  Timer &T = (*NamedTimers)[Name];
  if (!T.isInitialized())
    T.init(Name);
  return T;
}
