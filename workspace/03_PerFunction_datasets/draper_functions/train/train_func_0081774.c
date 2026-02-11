val_nodeset(String *nodeset)
{
  prepare(nodeset);
  for (MY_XPATH_FLT *flt= fltbeg; flt < fltend; flt++)
  {
    uint pos= 0;
    MY_XML_NODE *self= &nodebeg[flt->num];
    if (validname(self))
      ((XPathFilter*)nodeset)->append_element(flt->num,pos++);
  }
  return nodeset;
}
