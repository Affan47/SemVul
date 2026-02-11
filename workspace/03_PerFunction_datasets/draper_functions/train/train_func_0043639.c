strlist_merge (m1, m2)
     STRINGLIST *m1, *m2;
{
  STRINGLIST *sl;
  int i, n, l1, l2;

  l1 = m1 ? m1->list_len : 0;
  l2 = m2 ? m2->list_len : 0;

  sl = strlist_create (l1 + l2 + 1);
  for (i = n = 0; i < l1; i++, n++)
    sl->list[n] = STRDUP (m1->list[i]);
  for (i = 0; i < l2; i++, n++)
    sl->list[n] = STRDUP (m2->list[i]);
  sl->list_len = n;
  sl->list[n] = (char *)NULL;
  return (sl);
}
