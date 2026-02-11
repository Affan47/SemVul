maxabs()
{
  if (maxdef) return v[amax - 1].abs;
  max();
  return v[amax - 1].abs;
}
