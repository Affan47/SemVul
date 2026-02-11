tell_bots(int idx)
{
  char s[512];
  int i;
  tand_t *bot;

  if (!tands) {
    dprintf(idx, "%s\n", BOT_NOBOTSLINKED);
    return;
  }
  strcpy(s, botnetnick);
  i = strlen(botnetnick);

  for (bot = tandbot; bot; bot = bot->next) {
    if (i > (500 - HANDLEN)) {
      dprintf(idx, "Bots: %s\n", s);
      s[0] = 0;
      i = 0;
    }
    if (i) {
      s[i++] = ',';
      s[i++] = ' ';
    }
    strcpy(s + i, bot->bot);
    i += strlen(bot->bot);
  }
  if (s[0])
    dprintf(idx, "Bots: %s\n", s);
  dprintf(idx, "%s: %d\n", MISC_TOTAL, tands + 1);
}
