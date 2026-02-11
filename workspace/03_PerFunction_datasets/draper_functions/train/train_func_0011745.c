ScalarIndex(int index) const
{
  if (index != 0 && index != 1)
    return 0;

  return E.scalar_ind[index];
}
