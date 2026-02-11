display_node (node_t * node)
{
  double diffms;

  if (!node)
    return FALSE;

  diffms = substract_times_ms(&appdata.now, &node->node_stats.stats.last_time);


  if (diffms >= pref.gui_node_timeout_time
      && pref.gui_node_timeout_time
      && !node->node_stats.pkt_list.length)
    return FALSE;

#if 1
  if ((pref.gui_node_timeout_time == 1) && !node->node_stats.pkt_list.length)
    g_my_critical ("Impossible situation in display node");
#endif

  return TRUE;
}
