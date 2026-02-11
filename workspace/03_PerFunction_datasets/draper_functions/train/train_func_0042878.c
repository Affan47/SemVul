parseArg()
{
  Param parm = parseParam();
  if (parm != nameParam && parm != literalParam) {
    message(CatalogMessages::nameOrLiteralExpected);
    return false;
  }
  return true;
}
