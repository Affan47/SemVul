rotate_sources (KKamPanel *p)
{
  GList *link;
  int times, i, len;

  if (p == NULL || p->sources == NULL ||
        (len = g_list_length (p->sources)) == 1)
    return;

  times = p->random ? (rand () % (len - 1) + 1) : 1;
  for (i = 0; i < times; i++)
  {
    link = p->sources;
    p->sources = g_list_remove_link (p->sources, link);
    p->sources = g_list_concat (p->sources, link);
  }
}
