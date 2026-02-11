lrmv ( LISTID lid )
{
  LIST * l;
  LISTNODE * p;

  l = (LIST *)lid;

  CKLMAGIC(l);

  p = l->bottom;

  if (p == NULL) {
    CKLMAGIC(l);
    return NULL;
  }
  else {
    CKLMAGIC(l);
    return remove_ln ( l, p );
  }
}
