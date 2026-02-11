stats_servers(struct Client *source_p)
{
  dlink_node *ptr = NULL;

  DLINK_FOREACH(ptr, serv_list.head)
  {
    const struct Client *target_p = ptr->data;

    sendto_one(source_p, ":%s %d %s v :%s (%s!%s@%s) Idle: %d",
               from, RPL_STATSDEBUG, to, target_p->name,
               (target_p->serv->by[0] ? target_p->serv->by : "Remote."),
               "*", "*", (int)(CurrentTime - target_p->lasttime));
  }

  sendto_one(source_p, ":%s %d %s v :%u Server(s)",
             from, RPL_STATSDEBUG, to, dlink_list_length(&serv_list));
}
