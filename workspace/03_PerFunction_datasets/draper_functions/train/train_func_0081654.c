cliPlayerList_disconnected(CliPlayerList *pl, const char *buf)  {
  char  name[50];
  int  args, playerNum;

  args = sscanf(buf, "{%s ", name);
  assert(args == 1);
  playerNum = cliPlayerList_lookupPlayer(pl, name);
  if (playerNum >= 0)  {
    pl->players[playerNum].state = cliPlayer_noPlayer;
    while ((pl->sortEnd > 0) &&
	   (pl->players[pl->sortEnd - 1].state == cliPlayer_noPlayer))
      --pl->sortEnd;
    if (pl->win)  {
      butList_changeLine(pl->list, playerNum, "");
      if (pl->players[playerNum].match)  {
	but_destroy(pl->players[playerNum].match);
	pl->players[playerNum].match = NULL;
      }
    }
  }
}
