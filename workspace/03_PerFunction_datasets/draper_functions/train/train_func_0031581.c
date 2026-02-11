q_tbuf(char *bot, char *s, struct chanset_t *chan)
{
  struct share_msgq *q;
  tandbuf *t;

  for (t = tbuf; t && t->bot[0]; t = t->next)
    if (!egg_strcasecmp(t->bot, bot)) {
      if (chan) {
        fr.match = (FR_CHAN | FR_BOT);
        get_user_flagrec(get_user_by_handle(userlist, bot), &fr, chan->dname);
      }
      if ((!chan || bot_chan(fr) || bot_global(fr)) &&
          (q = q_addmsg(t->q, chan, s)))
        t->q = q;
      break;
    }
}
