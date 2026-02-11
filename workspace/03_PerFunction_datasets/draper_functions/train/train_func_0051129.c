val_nodeset(String *nodeset)
{
  prepare(nodeset);
  for (MY_XPATH_FLT *flt= fltbeg; flt < fltend; flt++)
  {
    uint pos= 0;
    MY_XML_NODE *self= &nodebeg[flt->num];
    if (need_self && validname(self))
      ((XPathFilter*)nodeset)->append_element(flt->num,pos++);
    for (uint j= flt->num + 1 ; j < numnodes ; j++)
    {
      MY_XML_NODE *node= &nodebeg[j];
      if (node->level <= self->level)
        break;
      if ((node->type == MY_XML_NODE_TAG) && validname(node))
        ((XPathFilter*)nodeset)->append_element(j,pos++);
    }
  }
  return nodeset;
}
