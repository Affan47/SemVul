xdb_room_clear(cnr room)
{
  char *roomid;
  char *host;
  cni master;
  jid store;
  jid fulljid;
  xmlnode node;
  xmlnode item;
  pool p;

  if(room == NULL)
  {
    return;
  }

  p = pool_new();
  master = room->master;
  roomid = jid_full(room->id);
  host = room->id->server;

  fulljid = jid_new(p, spools(p, "rooms@", host, p));
  store = jid_new(p, spools(p, shahash(roomid), "@", host, p));

  log_debug(NAME, "[%s] asked to clear a room from xdb (%s)", FZONE, jid_full(room->id));


  node = xdb_get(master->xdbc, fulljid, "muc:room:list");

  if(node != NULL)
  {
    item = xmlnode_get_tag(node, spools(p, "?jid=", jid_full(jid_fix(store)), p));

    if(item)
    {
      log_debug(NAME, "[%s] Found (%s) in rooms.xml - removing, %s", FZONE, jid_full(room->id), jid_full(jid_fix(store)));
      xmlnode_hide(item);
      xdb_set(master->xdbc, fulljid, "muc:room:list", node);
    }
    else
    {
      log_debug(NAME, "[%s] (%s) not found in rooms.xml - ignoring, %s", FZONE, jid_full(room->id), jid_full(jid_fix(store)));
    }
  }


  xdb_set(master->xdbc, store, "muc:list:owner", NULL);
  xdb_set(master->xdbc, store, "muc:list:admin", NULL);
  xdb_set(master->xdbc, store, "muc:list:member", NULL);
  xdb_set(master->xdbc, store, "muc:list:outcast", NULL);


  xdb_set(master->xdbc, store, "muc:room:config", NULL);

  xmlnode_free(node);
  pool_free(p);

  return;
}
