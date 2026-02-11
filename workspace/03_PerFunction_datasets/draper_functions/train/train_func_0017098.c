subCost(ProfileCostArray* c)
{
  if (_realIndex != ProfileCostArray::InvalidIndex)
    return c->subCost(_realIndex);

  if (!_parsed) {
    if (!parseFormula()) return 0;
  }
  SubCost res = 0;

  int rc = _set->realCount();
  for (int i = 0;i<rc;i++)
    if (_coefficient[i] != 0)
      res += _coefficient[i] * c->subCost(i);

  return res;
}
