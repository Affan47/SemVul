sort_clist_by_id(Clist lst)
{
  int n = clist_length(lst);
  Topform *a = malloc(n * sizeof(Topform *));
  int i;
  Clist_pos p;

  for (p = lst->first, i = 0; p; p = p->next, i++)
    a[i] = p->c;

  clist_remove_all_clauses(lst);

  merge_sort((void **) a, n, (Ordertype (*)(void*, void*)) compare_clause_ids);

  for (i = 0; i < n; i++)
    clist_append(a[i], lst);

  free(a);
}
