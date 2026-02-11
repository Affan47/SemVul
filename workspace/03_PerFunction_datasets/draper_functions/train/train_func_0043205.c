updateHist(field_t *field[2], int nlevels, int gridsize, double *yvals, int onlyNorth)
{
  int levelID,i;

  for ( levelID = 0; levelID < nlevels; levelID++ )
    for ( i = 0; i < gridsize; i++ )
      if ( onlyNorth )
      {
        if ( yvals[i] >= 0.0 )
          field[1][levelID].ptr[i] = field[0][levelID].ptr[i];
      }
      else
        field[1][levelID].ptr[i] = field[0][levelID].ptr[i];
}
