DEF_side2a(aSide)
  char  aSide;
{
  static char *tTransf[] = { "N", "S", "W", "E" };


  switch (aSide) {
    case SOUTH:  return (tTransf[0]);
    case NORTH:  return (tTransf[1]);
    case EAST:  return (tTransf[2]);
    case WEST:  return (tTransf[3]);
  }

  return (tTransf[0]);
}
