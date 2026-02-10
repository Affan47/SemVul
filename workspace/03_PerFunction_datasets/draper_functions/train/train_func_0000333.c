remparty(char *bot, int sock)
{
  int i;

  for (i = 0; i < parties; i++)
    if ((!egg_strcasecmp(party[i].bot, bot)) && (party[i].sock == sock)) {
      parties--;
      if (party[i].from)
        nfree(party[i].from);
      if (party[i].away)
        nfree(party[i].away);
      if (i < parties) {
        strcpy(party[i].bot, party[parties].bot);
        strcpy(party[i].nick, party[parties].nick);
        party[i].chan = party[parties].chan;
        party[i].sock = party[parties].sock;
        party[i].flag = party[parties].flag;
        party[i].status = party[parties].status;
        party[i].timer = party[parties].timer;
        party[i].from = party[parties].from;
        party[i].away = party[parties].away;
      }
    }
}
