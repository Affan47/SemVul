GWEN_StringList__compar_desc_int(const void *a, const void *b) {
  const GWEN_STRINGLISTENTRY * const * pse1 = a, * const * pse2 = b;
  const GWEN_STRINGLISTENTRY *se1 = *pse1, *se2 = *pse2;
  if (se1 && se2 && se1->data && se2->data)
    return (atoi(se1->data)>atoi(se2->data));
  else
    return 0;
}
