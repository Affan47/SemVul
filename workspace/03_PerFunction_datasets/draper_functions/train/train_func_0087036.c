check_for_win()
{
  int x, y;
  if (untagged != 0)
    return;
  for (x=0; x<ct; x++)
    for (y=0; y<ct; y++)
      if (grid[x][y] > 8 && grid[x][y] != C_FLAG)
	return;
  set_penguin(PENGUIN_COOL);
}
