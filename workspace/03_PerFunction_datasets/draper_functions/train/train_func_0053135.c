iset_sort(struct ilist *a)
{
  if (a == NULL)
    return NULL;
  else {
    int i = a->i;
    struct ilist *b = iset_sort(a->next);
    free_ilist(a);
    return iset_add(i, b);
  }
}
