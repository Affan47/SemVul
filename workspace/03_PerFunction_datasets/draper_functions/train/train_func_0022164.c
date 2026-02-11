operator!=(const amount_t& amt) const
{
  if (commodity() != amt.commodity())
    return true;
  return compare(amt) != 0;
}
