sendto_common_channels_local(struct Client *user, int touser,
                             const char *pattern, ...)
{
  va_list args;
  dlink_node *uptr;
  dlink_node *cptr;
  struct Channel *chptr;
  struct Membership *ms;
  struct Client *target_p;
  char buffer[IRCD_BUFSIZE];
  int len;

  va_start(args, pattern);
  len = send_format(buffer, IRCD_BUFSIZE, pattern, args);
  va_end(args);

  ++current_serial;

  DLINK_FOREACH(cptr, user->channel.head)
  {
    chptr = ((struct Membership *) cptr->data)->chptr;
    assert(chptr != NULL);

    DLINK_FOREACH(uptr, chptr->members.head)
    {
      ms = uptr->data;
      target_p = ms->client_p;
      assert(target_p != NULL);

      if (!MyConnect(target_p) || target_p == user || IsDefunct(target_p) ||
          target_p->localClient->serial == current_serial)
        continue;

      target_p->localClient->serial = current_serial;
      send_message(target_p, buffer, len);
    }
  }

  if (touser && MyConnect(user) && !IsDead(user) &&
      user->localClient->serial != current_serial)
    send_message(user, buffer, len);
}
