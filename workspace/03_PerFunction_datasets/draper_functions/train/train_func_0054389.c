link_delete(link_t *link)
{
  guint i;

  g_assert(link);


  delete_conversation_link (&link->link_id.src.addr.ip,
                            &link->link_id.dst.addr.ip);

  for (i = STACK_SIZE; i + 1; i--)
    if (link->main_prot[i])
      {
        g_free (link->main_prot[i]);
        link->main_prot[i] = NULL;
      }

  traffic_stats_reset(&link->link_stats);

  g_free (link);
}
