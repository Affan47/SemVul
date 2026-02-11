check_chanlist_hand(const char *hand)
{
  register struct chanset_t *chan;
  register memberlist *m;

  for (chan = chanset; chan; chan = chan->next)
    for (m = chan->channel.member; m && m->nick[0]; m = m->next)
      if (m->user && !egg_strcasecmp(m->user->handle, hand))
        return m->user;
  return NULL;
}
