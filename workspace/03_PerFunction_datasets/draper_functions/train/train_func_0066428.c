init_amsr_day(int vlistID, int gridID, int zaxisID, int nvars)
{


  char *name[]  = {"hours", "sst", "wind", "vapor", "cloud", "rain"};
  char *units[] = {"h", "deg Celcius", "m/s", "mm", "mm", "mm/h"};
  double xscale[]  = {0.1, 0.15, 0.2, 0.3, 0.01, 0.1};
  double xminval[] = {0., -3., 0., 0., 0., 0.};
  int i, varID;

  for ( i = 0; i < nvars; ++i )
    {
      varID = vlistDefVar(vlistID, gridID, zaxisID, TSTEP_INSTANT);
      vlistDefVarName(vlistID, varID, name[i]);
      vlistDefVarUnits(vlistID, varID, units[i]);
      vlistDefVarDatatype(vlistID, varID, DATATYPE_INT16);
      vlistDefVarMissval(vlistID, varID, 254);
      vlistDefVarScalefactor(vlistID, varID, xscale[i]);
      vlistDefVarAddoffset(vlistID, varID, xminval[i]);
    }
}
