printQuasi(int *isec2)
{


  char yout[64];
  int nextlat, nrepeat, latcnt;
  int j;
  int ntos;


  fprintf(grprsm, "  Number of points along a parallel varies.\n");

  ntos = ( fmod((double) isec2[10], 128.) < 64 );

  if ( ntos )
    fprintf(grprsm, "  Number of points.   Parallel. (North to South)\n");
  else
    fprintf(grprsm, "  Number of points.   Parallel. (South to North)\n");


  latcnt  = isec2[2];
  nextlat = 0;
  memset(yout, ' ', (size_t) 11);

  for ( j = 0; j < latcnt; j++ )
    {
      nextlat = nextlat + 1;
      sprintf(yout, "%4d", nextlat);


      if ( nextlat > latcnt ) break;
      if ( nextlat == latcnt )
	{
	  fprintf(grprsm, " %5d                %-12s\n", isec2[nextlat+21], yout);
	  break;
	}


      nrepeat = 0;

    LABEL110:


      if ( isec2[nextlat+21+1] == isec2[nextlat+21] )
	{
          nrepeat = nrepeat + 1;
          nextlat = nextlat + 1;
	  if ( nextlat < latcnt ) goto LABEL110;
	}


      if ( nrepeat >= 1 )
	{
	  strncpy(yout+4, " to", 3);
	  sprintf(yout+7, "%5d", nextlat);
        }
      fprintf(grprsm, " %5d                %-12s\n", isec2[nextlat+21], yout);
      memset(yout, ' ', (size_t) 11);
    }
}
