parse_events (const gchar *events)
{
  gchar **ranges_strv;
  GList *ranges = NULL;
  int i;

  ranges_strv = g_strsplit (events, ",", 0);

  for (i = 0; ranges_strv[i]; i++)
  {
    struct event_range *er = g_slice_new (struct event_range);
    gchar *p = NULL;

    er->first = atoi (ranges_strv[i]);
    p = strchr (ranges_strv[i], '-');
    if (p)
      er->last = atoi (p + 1);
    else
      er->last = er->first;

    ranges = g_list_insert_sorted (ranges, er, event_range_cmp);
  }

  g_strfreev (ranges_strv);

  return ranges;
}
