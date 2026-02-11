away_notes(char *bot, int sock, char *msg)
{
  int idx = findanyidx(sock);

  if (egg_strcasecmp(bot, botnetnick))
    return;
  if (msg && msg[0])
    dprintf(idx, "%s\n", NOTES_STORED);
  else
    notes_read(dcc[idx].nick, 0, "+", idx);
}
