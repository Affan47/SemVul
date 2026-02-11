val_nodeset(String *nodeset)
{
  Item_nodeset_func *nodeset_func= (Item_nodeset_func*) args[0];
  prepare(nodeset);
  MY_XPATH_FLT *flt;
  uint pos, size= fltend - fltbeg;
  for (pos= 0, flt= fltbeg; flt < fltend; flt++)
  {
    nodeset_func->context_cache.length(0);
    ((XPathFilter*)(&nodeset_func->context_cache))->append_element(flt->num,
                                                                   flt->pos,
                                                                   size);
    int index= (int) (args[1]->val_int()) - 1;
    if (index >= 0 && (flt->pos == (uint) index || args[1]->is_bool_func()))
      ((XPathFilter*)nodeset)->append_element(flt->num, pos++);
  }
  return nodeset;
}
