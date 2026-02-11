cmd_white(void)
{


  NewPosition();
  CLEAR ( flags, THINK);
  CLEAR ( flags, MANUAL);
  CLEAR (flags, TIMEOUT);
  computer = black;
  if ( board.side == black ){
    board.side = white;
    board.ep = -1;
  }
}
