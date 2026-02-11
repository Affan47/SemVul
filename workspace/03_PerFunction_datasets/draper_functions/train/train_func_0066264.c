con_room_nick(cnr room, cnu user, xmlnode x)
{
  char *nick = NULL;
  xmlnode cur;
  int count = 1;

  if(room == NULL || user == NULL)
  {
    log_warn(NAME, "[%s] Aborting - NULL attribute found", FZONE);
    return NULL;
  }

  log_debug(NAME, "[%s] looking for valid nick in room %s from starter %s", FZONE, jid_full(room->id), xmlnode2str(x));


  if(x == NULL)
  {
    nick = pmalloco(user->p, j_strlen(user->realid->user) + 10);
    log_debug(NAME, "[%s] Malloc: Nick = %d", FZONE, j_strlen(user->realid->user) + 10);

    sprintf(nick, "%s", user->realid->user);
    while(g_hash_table_lookup(room->local, nick) != NULL)
      sprintf(nick, "%s%d", user->realid->user,count++);
    return nick;
  }


  for(cur = x; cur != NULL; cur = xmlnode_get_nextsibling(cur))
  {
    if(j_strcmp(xmlnode_get_name(cur),"nick") == 0 && (nick = xmlnode_get_data(cur)) != NULL)
      if(g_hash_table_lookup(room->local, nick) == NULL)
        break;
  }

  if(is_registered(room->master, jid_full(jid_user(user->realid)), nick) == -1)
    nick = NULL;

  return nick;
}
