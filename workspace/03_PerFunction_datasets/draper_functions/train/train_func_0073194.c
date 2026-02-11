matchPressed(But *but)  {
  CliPlayerList  *pl = but_packet(but);
  int  playerNum, oppRank, myRank;
  CliPlayer  *p, *me;
  const char  *rankStr;

  assert(MAGIC(pl));


  for (playerNum = 0;  pl->players[playerNum].match != but;  ++playerNum)  {
    assert(playerNum < pl->maxPlayers);
  }
  p = &pl->players[playerNum];
  for (playerNum = 0;
       (pl->players[playerNum].state == cliPlayer_noPlayer) ||
       strcmp(str_chars(&pl->players[playerNum].name),
	      str_chars(&pl->data->userName));
       ++playerNum)  {
    if (playerNum + 1 >= pl->maxPlayers)  {

      cgoban_createMsgWindow(pl->data->cg, "Cgoban Error", msg_youDontExist);
      return(BUTOUT_ERR);
    }
  }
  me = &pl->players[playerNum];
  if (isdigit(str_chars(&p->rank)[0]) && isdigit(str_chars(&me->rank)[0]))  {
    oppRank = atoi(str_chars(&p->rank));
    rankStr = str_chars(&p->rank);
    if ((rankStr[str_len(&p->rank) - 1] == 'k') ||
	(rankStr[str_len(&p->rank) - 2] == 'k'))
      oppRank = -oppRank;
    myRank = atoi(str_chars(&me->rank));
    rankStr = str_chars(&me->rank);
    if ((rankStr[str_len(&me->rank) - 1] == 'k') ||
	(rankStr[str_len(&me->rank) - 2] == 'k'))
      myRank = -myRank;
  } else
    oppRank = myRank = 0;
  cliMatch_create(pl->data, str_chars(&p->name), &pl->match, myRank - oppRank);
  return(0);
}
