sub_lang(int idx, char *text)
{
  char s[1024];
  struct flag_record fr = { FR_GLOBAL | FR_CHAN, 0, 0, 0, 0, 0 };

  get_user_flagrec(dcc[idx].user, &fr, dcc[idx].u.chat->con_chan);
  help_subst(NULL, NULL, 0,
             (dcc[idx].status & STAT_TELNET) ? 0 : HELP_IRC, NULL);
  strncpyz(s, text, sizeof s);
  if (s[strlen(s) - 1] == '\n')
    s[strlen(s) - 1] = 0;
  if (!s[0])
    strcpy(s, " ");
  help_subst(s, dcc[idx].nick, &fr, 1, botnetnick);
  if (s[0])
    dprintf(idx, "%s\n", s);
}
