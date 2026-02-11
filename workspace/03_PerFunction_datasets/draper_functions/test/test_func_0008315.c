remove_null_literals(Literals l)
{
  if (l == NULL)
    return NULL;
  else {
    l->next = remove_null_literals(l->next);
    if (l->atom != NULL)
      return l;
    else {
      Literals m = l->next;
      free_literals(l);
      return m;
    }
  }
}
