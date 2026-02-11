distance(const Vector &v) const
{
  Vector dir = iQ - iP;
  Vector udir;
  double len = dir.factorize(udir);
  double dx = dot(udir, v - iP);
  if (dx <= 0)
    return (v - iP).len();
  if (dx >= len)
    return (v - iQ).len();
  return (v - (iP + dx * udir)).len();
}
