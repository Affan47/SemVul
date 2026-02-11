WuTopStat(box * cube, unsigned char dir, int pos, int *m)
{
  switch(dir)
  {
    case RED:
      return ( m[indx(pos, cube->g1, cube->b1)]
              -m[indx(pos, cube->g1, cube->b0)]
              -m[indx(pos, cube->g0, cube->b1)]
              +m[indx(pos, cube->g0, cube->b0)] );
      break;
    case GREEN:
      return ( m[indx(cube->r1, pos, cube->b1)]
              -m[indx(cube->r1, pos, cube->b0)]
              -m[indx(cube->r0, pos, cube->b1)]
              +m[indx(cube->r0, pos, cube->b0)] );
      break;
    case BLUE:
      return ( m[indx(cube->r1, cube->g1, pos)]
              -m[indx(cube->r1, cube->g0, pos)]
              -m[indx(cube->r0, cube->g1, pos)]
              +m[indx(cube->r0, cube->g0, pos)] );
      break;
  }
  return 0;
}
