check_consistency() const
{
  const size_t sz = NumberOfFeatures();
  if (sz == 0)
    return true;

  for (featarray_t::const_iterator i = m_array.begin(); i != m_array.end(); i++) {
    if (i->size() != sz)
      return false;
  }
  return true;
}
