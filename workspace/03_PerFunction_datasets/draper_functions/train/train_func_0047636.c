copy_glist_of_ilists(struct glist *a)
{
  if (a == NULL)
    return NULL;
  else {
    struct glist *b = get_glist();
    b->v = copy_ilist(a->v);
    b->next = copy_glist_of_ilists(a->next);
    return b;
  }
}
