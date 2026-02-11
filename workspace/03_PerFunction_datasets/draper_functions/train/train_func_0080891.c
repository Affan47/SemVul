protocol_t_dump(const protocol_t *prot)
{
  gchar *msg;
  gchar *msg_stats;
  gchar *msg_names;

  if (!prot)
    return g_strdup("protocol_t NULL");

  msg_stats = basic_stats_dump(&prot->stats);

  if (!prot->node_names)
    msg_names = g_strdup("-- no names --");
  else
    {
      const GList *cur_el;
      msg_names = NULL;
      cur_el = prot->node_names;
      while (cur_el)
        {
          gchar *str_name;
          const name_t *cur_name;

          cur_name = (const name_t *)(cur_el->data);
          str_name = node_name_dump(cur_name);
          if (!msg_names)
            msg_names = str_name;
          else
            {
              gchar *tmp = msg_names;
              msg_names = g_strjoin(",", tmp, str_name, NULL);
              g_free(tmp);
              g_free(str_name);
            }
          cur_el = cur_el->next;
        }
    }

  msg = g_strdup_printf("protocol name: %s, stats [%s], "
                         "node_names [%s]",
                         prot->name, msg_stats, msg_names);

  g_free(msg_stats);
  g_free(msg_names);
  return msg;
}
