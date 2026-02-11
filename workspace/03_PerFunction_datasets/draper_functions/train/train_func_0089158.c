dxml_next_notPCDATA(dxml_element * e)
{
  if (!e) return NULL ;
  if (e->element_type == element_type_pcdata)
    return dxml_next_notPCDATA(e->next);
  return e;
}
