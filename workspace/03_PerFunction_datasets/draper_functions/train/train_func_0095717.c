operator== (const t_path& lhs, const t_path& rhs) {
  if (lhs.size() != rhs.size())
    return false;

  t_path_cit lhs_it = lhs.begin();
  t_path_cit rhs_it = rhs.begin();

  for (; lhs_it != lhs.end(); ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it)
      return false;
  }
  return true;
}
