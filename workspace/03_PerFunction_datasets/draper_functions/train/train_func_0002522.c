mode_invite_clear(struct Channel *chan)
{
  while (chan->invites)
    del_invite(chan->invites->value.cptr, chan);
}
