hasPOVBoundary() const
{
  if (__dirichletList->hasPOVBoundary()) return true;
  if (__variationalFormula->hasPOVBoundary()) return true;
  return false;
}
