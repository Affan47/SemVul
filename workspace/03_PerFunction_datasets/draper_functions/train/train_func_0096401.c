getLastArg(OptSpecifier Id0, OptSpecifier Id1,
                         OptSpecifier Id2) const {
  Arg *Res = nullptr;
  for (const_iterator it = begin(), ie = end(); it != ie; ++it) {
    if ((*it)->getOption().matches(Id0) ||
        (*it)->getOption().matches(Id1) ||
        (*it)->getOption().matches(Id2)) {
      Res = *it;
      Res->claim();
    }
  }

  return Res;
}
