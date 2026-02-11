threat_combo (struct board *board, struct threat_combo *tc)
{
  short x, y, z = 0;


  for (y = 2; y < BOARDY; y += 2)
    for (x = 0; x < BOARDX; x++)
      if (board->stack[x] < y)
	check_double_threat (board, x, y, tc, &z);

  return z;
}
