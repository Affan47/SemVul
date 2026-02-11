IsPrefix(const ArgPromotion::IndicesVector &Prefix,
                     const ArgPromotion::IndicesVector &Longer) {
  if (Prefix.size() > Longer.size())
    return false;
  for (unsigned i = 0, e = Prefix.size(); i != e; ++i)
    if (Prefix[i] != Longer[i])
      return false;
  return true;
}
