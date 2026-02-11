nPrecedingCharRefs(Index ind) const
{
  size_t i;


  if (charRefs_.size() == 0
      || ind > charRefs_.back().replacementIndex)

    i = charRefs_.size();
  else {


    i = 0;
    size_t lim = charRefs_.size();
    while (i < lim) {
      size_t mid = i + (lim - i)/2;
      if (charRefs_[mid].replacementIndex >= ind)
	lim = mid;
      else
	i = mid + 1;
    }
  }
  return i;
}
