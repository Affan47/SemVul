lookupInfoImpl(Triple T) {
  std::unique_ptr<TargetLibraryInfoImpl> &Impl =
      Impls[T.normalize()];
  if (!Impl)
    Impl.reset(new TargetLibraryInfoImpl(T));

  return *Impl;
}
