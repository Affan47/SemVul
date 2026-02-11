inf_adopted_session_find_next_noop_user(InfAdoptedSession* session)
{
  InfAdoptedSessionPrivate* priv;
  GSList* item;
  InfAdoptedSessionLocalUser* local;
  InfAdoptedSessionLocalUser* next_user;

  priv = INF_ADOPTED_SESSION_PRIVATE(session);
  next_user = NULL;

  for(item = priv->local_users; item != NULL; item = g_slist_next(item))
  {
    local = (InfAdoptedSessionLocalUser*)item->data;
    if(local->noop_time != 0)
      if(next_user == NULL || local->noop_time < next_user->noop_time)
        next_user = local;
  }

  return next_user;
}
