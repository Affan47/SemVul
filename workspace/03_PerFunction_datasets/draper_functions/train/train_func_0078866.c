nametestfunc(MY_XPATH *xpath,
                          int type, Item *arg, const char *beg, uint len)
{
  DBUG_ASSERT(arg != 0);
  DBUG_ASSERT(arg->type() == Item::XPATH_NODESET);
  DBUG_ASSERT(beg != 0);
  DBUG_ASSERT(len > 0);

  Item *res;
  switch (type)
  {
  case MY_XPATH_AXIS_ANCESTOR:
    res= new Item_nodeset_func_ancestorbyname(arg, beg, len, xpath->pxml, 0);
    break;
  case MY_XPATH_AXIS_ANCESTOR_OR_SELF:
    res= new Item_nodeset_func_ancestorbyname(arg, beg, len, xpath->pxml, 1);
    break;
  case MY_XPATH_AXIS_PARENT:
    res= new Item_nodeset_func_parentbyname(arg, beg, len, xpath->pxml);
    break;
  case MY_XPATH_AXIS_DESCENDANT:
    res= new Item_nodeset_func_descendantbyname(arg, beg, len, xpath->pxml, 0);
    break;
  case MY_XPATH_AXIS_DESCENDANT_OR_SELF:
    res= new Item_nodeset_func_descendantbyname(arg, beg, len, xpath->pxml, 1);
    break;
  case MY_XPATH_AXIS_ATTRIBUTE:
    res= new Item_nodeset_func_attributebyname(arg, beg, len, xpath->pxml);
    break;
  case MY_XPATH_AXIS_SELF:
    res= new Item_nodeset_func_selfbyname(arg, beg, len, xpath->pxml);
    break;
  default:
    res= new Item_nodeset_func_childbyname(arg, beg, len, xpath->pxml);
  }
  return res;
}
