claimeven (struct board *board)
{
  short x1, y1, q1, q2;
  short sln, *grp, j;


  for (y1 = 1; y1 < BOARDY; y1 += 2)
    for (x1 = 0; x1 < BOARDX; x1++) {
      if (!board->sqused[ELM (x1, y1)])
	continue;

      board->solution[board->sp]->solgroupsnumb = 0;

      q1 = ELM (x1, y1);
      q2 = ELM (x1, y1 - 1);

      if (board->square[q1] == EMPTY &&
	  board->square[q2] == EMPTY && board->sqused[q2]) {
	sln = board->solvable_groups->sqpnt[q1];
	grp = board->solvable_groups->square[q1];

	for (j = 0; j < sln; j++)
	  if (board->intgp.tgroups[grp[j]] == YES) {
	    if (board->solution[board->sp]->solgroupsnumb == 0) {
	      board->solution[board->sp]->solname = CLAIMEVEN;
	      board->solution[board->sp]->solpoint[0] = q1;
	      board->solution[board->sp]->solpoint[1] = q2;
	      board->solution[board->sp]->sqinv[0] = q1;
	      board->solution[board->sp]->sqinv[1] = q2;
	      board->solution[board->sp]->sqinvnumb = 2;
	      board->instances[CLAIMEVEN]++;
	    }
	    board->solution[board->sp]->solgroups[board->solution[board->sp]->
						  solgroupsnumb++] = grp[j];
	  }
      }

      if (board->solution[board->sp]->solgroupsnumb > 0)
	board->sp++;
    }
}
