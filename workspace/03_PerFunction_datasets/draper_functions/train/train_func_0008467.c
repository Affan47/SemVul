_con_beat_idle(gpointer key, gpointer data, gpointer arg)
{
  cnr room = (cnr)data;
  time_t t = *(time_t *)arg;
  xmlnode node;
  char *user_name;

  log_debug(NAME, "[%s] HBTICK: Idle check for >%s<", FZONE, (char*) key);

  if(room == NULL)
  {
    log_warn(NAME, "[%s] Aborting : NULL cnr for %s", FZONE, (char*) key);
    return;
  }


  room->queue = g_queue_new();
  g_hash_table_foreach(room->remote, _con_beat_user, &t);

  while ((user_name = (char *)g_queue_pop_head(room->queue)) != NULL)
  {
    node = xmlnode_new_tag("reason");
    xmlnode_insert_cdata(node, "Clearing zombie", -1);

    con_user_zap(g_hash_table_lookup(room->remote, user_name), node);

    log_debug(NAME, "[%s] HBTICK: removed zombie '%s' in the queue", FZONE, user_name);
    g_free(user_name);
  }
  g_queue_free(room->queue);


  if(room->persistent == 0 && room->count == 0 && (t - room->last) > 240)
  {
    log_debug(NAME, "[%s] HBTICK: Locking room and adding %s to remove queue", FZONE, (char*) key);
    room->locked = 1;
    g_queue_push_tail(room->master->queue, g_strdup(jid_full(room->id)));
  }
}
