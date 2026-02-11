play_break_through_n(int color, int num_moves, ...)
{
  va_list ap;
  int mcolor = color;
  int success = 0;
  int i;
  int played_moves = 0;
  int apos;
  int xpos;
  int ypos;
  int zpos;

  va_start(ap, num_moves);


  for (i = 0; i < num_moves; i++) {
    apos = va_arg(ap, int);

    if (apos != NO_MOVE
	&& (trymove(apos, mcolor, "play_break_through_n", NO_MOVE)
	    || tryko(apos, mcolor, "play_break_through_n")))
      played_moves++;
    mcolor = OTHER_COLOR(mcolor);
  }


  xpos = va_arg(ap, int);
  ypos = va_arg(ap, int);
  zpos = va_arg(ap, int);


#if 0
  modify_depth_values(played_moves);
#endif

  if (board[xpos] == EMPTY
      || board[ypos] == EMPTY
      || board[zpos] == EMPTY)
    success = 1;
  else
    success = break_through(xpos, ypos, zpos);

#if 0
  modify_depth_values(-played_moves);
#endif


  for (i = 0; i < played_moves; i++)
    popgo();

  va_end(ap);
  return success;
}
