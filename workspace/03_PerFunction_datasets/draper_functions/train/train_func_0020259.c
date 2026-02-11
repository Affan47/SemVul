lsrch ( LISTID lid, void * p, int (* compare)(void * p1, void * p2) )
{
  LIST * l;
  LISTNODE * ln;

  l = (LIST *)lid;

  CKLMAGIC(l);

  ln = l->top;

  while (ln!=NULL) {
    CKMAGIC(ln);
    if (compare(p,ln->data) == 0) {
      CKLMAGIC(l);
      return ln->data;
    }
    else {
      ln = ln->next;
    }
  }

  CKLMAGIC(l);
  return NULL;
}
