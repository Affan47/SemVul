getLastArg(OptSpecifier Id0, OptSpecifier Id1,
                         OptSpecifier Id2, OptSpecifier Id3,
                         OptSpecifier Id4, OptSpecifier Id5,
                         OptSpecifier Id6, OptSpecifier Id7) const {
  Arg *Res = nullptr;
  for (const_iterator it = begin(), ie = end(); it != ie; ++it) {
    if ((*it)->getOption().matches(Id0) ||
        (*it)->getOption().matches(Id1) ||
        (*it)->getOption().matches(Id2) ||
        (*it)->getOption().matches(Id3) ||
        (*it)->getOption().matches(Id4) ||
        (*it)->getOption().matches(Id5) ||
        (*it)->getOption().matches(Id6) ||
        (*it)->getOption().matches(Id7)) {
      Res = *it;
      Res->claim();
    }
  }

  return Res;
}
