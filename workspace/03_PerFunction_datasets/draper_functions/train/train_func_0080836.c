remove_supersets(struct glist *a, struct ilist *s)
{
  if (a == NULL)
    return NULL;
  else if (iset_subset(s, a->v)) {
    struct glist *b = a->next;
    free_ilist_list(a->v);
    free_glist(a);
    return remove_supersets(b, s);
  }
  else {
    a->next = remove_supersets(a->next, s);
    return a;
  }
}
