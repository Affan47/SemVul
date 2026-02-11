channels_prerehash()
{
  struct chanset_t *chan;


  for (chan = chanset; chan; chan = chan->next) {
    chan->status |= CHAN_FLAGGED;

    if (chan->status & CHAN_STATIC)
      chan->status &= ~CHAN_STATIC;
  }
  setstatic = 1;
}
