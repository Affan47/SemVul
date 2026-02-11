impliedSourceLinkRules()
{
  size_t n = linkProcess_.nImpliedLinkRules();
  Vector<size_t> sortOrder(n);
  size_t i;
  for (i = 0; i < n; i++)
    sortOrder[i] = i;
  for (i = 1; i < n; i++) {
    size_t tem = sortOrder[i];
    const StringC &name
      = linkProcess_.impliedLinkRule(tem).elementType->name();
    size_t j;
    for (j = i; j > 0; j--) {
      if (lexCmp(linkProcess_.impliedLinkRule(j - 1).elementType->name(),
		 name) <= 0)
	break;
      sortOrder[j] = sortOrder[j - 1];
    }
    sortOrder[j] = tem;
  }
  for (i = 0; i < n; i++) {
    const ResultElementSpec &result
      = linkProcess_.impliedLinkRule(sortOrder[i]);
    os() << '[' << result.elementType->name();
    if (result.attributeList.size() > 0) {
      os() << nl;
      attributeInfo(result.attributeList, resultAttribute);
    }
    os() << ']' << nl;
  }
}
