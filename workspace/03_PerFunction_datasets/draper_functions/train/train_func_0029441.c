getLastArgNoClaim(OptSpecifier Id0, OptSpecifier Id1) const {

  for (const_reverse_iterator it = rbegin(), ie = rend(); it != ie; ++it)
    if ((*it)->getOption().matches(Id0) ||
        (*it)->getOption().matches(Id1))
      return *it;
  return nullptr;
}
