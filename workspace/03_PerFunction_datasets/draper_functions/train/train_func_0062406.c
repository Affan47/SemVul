channels_expmem()
{
  int tot = 0, i;
  struct chanset_t *chan;

  for (chan = chanset; chan; chan = chan->next) {
    tot += sizeof(struct chanset_t);

    tot += strlen(chan->channel.key) + 1;
    if (chan->channel.topic)
      tot += strlen(chan->channel.topic) + 1;
    tot += (sizeof(struct memstruct) * (chan->channel.members + 1));

    tot += expmem_masklist(chan->channel.ban);
    tot += expmem_masklist(chan->channel.exempt);
    tot += expmem_masklist(chan->channel.invite);

    for (i = 0; i < MODES_PER_LINE_MAX && chan->cmode[i].op; i++)
      tot += strlen(chan->cmode[i].op) + 1;
    if (chan->key)
      tot += strlen(chan->key) + 1;
    if (chan->rmkey)
      tot += strlen(chan->rmkey) + 1;
  }
  tot += expmem_udef(udef);
  if (lastdeletedmask)
    tot += strlen(lastdeletedmask) + 1;
  return tot;
}
