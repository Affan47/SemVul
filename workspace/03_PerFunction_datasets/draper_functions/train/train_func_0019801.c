redraw()
{
  int x, y, z;
  if (defer_redraw)
    return;
  for (z=0; z<GRID_SZ; z++)
  {
    for (x=GRID_SX-1; x>=0; x--)
      for (y=0; x+y<GRID_SX && y<GRID_SY; y++)
	if (grid[x+y][y][z])
	  redraw_tile(x+y, y, z);
    for (y=0; y<GRID_SY; y++)
      for (x=0; x+y<GRID_SY && x<GRID_SX; x++)
	if (grid[x][x+y][z])
	  redraw_tile(x, x+y, z);
  }
  redraw_free_tile_count();
}
