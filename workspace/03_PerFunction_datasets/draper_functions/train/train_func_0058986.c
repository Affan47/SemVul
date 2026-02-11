shareout_but EGG_VARARGS_DEF(struct chanset_t *, arg1)
{
  int i, x, l;
  char *format;
  char s[601];
  struct chanset_t *chan;
  va_list va;

  chan = EGG_VARARGS_START(struct chanset_t *, arg1, va);
  x = va_arg(va, int);
  format = va_arg(va, char *);

  strcpy(s, "s ");
  if ((l = egg_vsnprintf(s + 2, 509, format, va)) < 0)
    s[2 + (l = 509)] = 0;
  for (i = 0; i < dcc_total; i++)
    if ((dcc[i].type->flags & DCT_BOT) && (i != x) &&
        (dcc[i].status & STAT_SHARE) &&
        (!(dcc[i].status & STAT_GETTING)) &&
        (!(dcc[i].status & STAT_SENDING))) {
      if (chan) {
        fr.match = (FR_CHAN | FR_BOT);
        get_user_flagrec(dcc[i].user, &fr, chan->dname);
      }
      if (!chan || bot_chan(fr) || bot_global(fr))
        tputs(dcc[i].sock, s, l + 2);
    }
  q_resync(s, chan);
  va_end(va);
}
