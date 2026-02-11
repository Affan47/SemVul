gribRepair1(int nrec, long recsize, unsigned char *gribbuffer)
{
  int level, nerr;
  unsigned char *pds = NULL, *gds = NULL, *bms = NULL, *bds = NULL;
  double cr = 1;

  nerr = grib1Sections(gribbuffer, recsize, &pds, &gds, &bms, &bds);
  if ( nerr )
    {
      fprintf(stdout, "%5d : error\n", nrec);
      return;
    }

  if ( PDS_LevelType == 100 )
    level = PDS_Level * 100;
  else if ( PDS_LevelType == 99 )
    level = PDS_Level;
  else
    level = PDS_Level1;

  if ( ((BDS_Flag >> 4)&1) && BDS_Z == 128 )
    {
      int s1, s2;
      s1 = ((int) ((bds[17]<<16)+(bds[18]<<8)+bds[19]));
      s2 = ((int) ((bds[20]<<16)+(bds[21]<<8)+bds[22]));
      cr = ((double)s1)/s2;
    }

  if ( IS_EQUAL(cr, 1) && BDS_NumBits == 24 )
    {
      fprintf(stdout, "Repair GRIB record %5d : code = %4d   level = %7d\n", nrec, PDS_Parameter, level);
      repair1(gribbuffer, recsize);
    }
}
