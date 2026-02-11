WuBottomStat(box * cube, unsigned char dir, int *m)
{
  switch(dir)
  {
    case RED:
      return ( -m[indx(cube->r0, cube->g1, cube->b1)]
               +m[indx(cube->r0, cube->g1, cube->b0)]
               +m[indx(cube->r0, cube->g0, cube->b1)]
               -m[indx(cube->r0, cube->g0, cube->b0)] );
      break;
    case GREEN:
      return ( -m[indx(cube->r1, cube->g0, cube->b1)]
               +m[indx(cube->r1, cube->g0, cube->b0)]
               +m[indx(cube->r0, cube->g0, cube->b1)]
               -m[indx(cube->r0, cube->g0, cube->b0)] );
      break;
    case BLUE:
      return ( -m[indx(cube->r1, cube->g1, cube->b0)]
               +m[indx(cube->r1, cube->g0, cube->b0)]
               +m[indx(cube->r0, cube->g1, cube->b0)]
               -m[indx(cube->r0, cube->g0, cube->b0)] );
      break;
  }
  return 0;
}
