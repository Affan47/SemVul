addEmpty(GoBoard *board, int loc)  {
  GoBoardPiece  *remove, *group, *neighbor, *oppList[4];
  GoStone  type;
  int  killedLocs[GOBOARD_MAXSIZE*GOBOARD_MAXSIZE];
  int  i, dir, numKilled, oppListLen;


  remove = board->pieces + loc;
  type = remove->type;
  if (type == goStone_empty)
    return;
  assert((type == goStone_white) || (type == goStone_black));
  numKilled = 0;
  for (group = remove->head;  group;  group = group->next)  {
    if (group != remove)
      killedLocs[numKilled++] = group - board->pieces;
    board->hashVal = goHash_xor(board->hashVal, group->hashStone[type]);
    group->type = goStone_empty;
    group->head = NULL;
    oppListLen = 0;
    for (dir = 0;  dir < 4;  ++dir)  {
      neighbor = group + board->dirs[dir];
      if (neighbor->type == goStone_opponent(type))  {
	neighbor = neighbor->head;
	++neighbor->libs;
	for (i = 0;  i < oppListLen;  ++i)  {
	  if (oppList[i] == neighbor)  {
	    --neighbor->libs;
	    break;
	  }
	}
	oppList[oppListLen++] = neighbor;
      }
    }
  }

  for (i = 0;  i < numKilled;  ++i)  {
    goBoard_addStone(board, type, killedLocs[i], NULL);
  }
}
