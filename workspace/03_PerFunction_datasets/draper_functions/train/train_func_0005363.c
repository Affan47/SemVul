list_clear (GList *ab)
{
  GList *l;

  for (l = ab; l; l = l->next)
    ab = g_list_remove_link (ab, l);
  ab = NULL;
}
