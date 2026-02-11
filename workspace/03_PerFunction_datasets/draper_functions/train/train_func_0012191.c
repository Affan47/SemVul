gridDefLcc2(int gridID, double earth_radius, double lon_0, double lat_0, double lat_1, double lat_2)
{
  grid_t *gridptr;

  if ( reshGetStatus ( gridID, &gridOps ) == CLOSED )
    {
      xwarning("%s", "Operation not executed.");
      return;
    }

  gridptr = ( grid_t *) reshGetVal ( gridID, &gridOps );

  grid_check_ptr(gridID, gridptr);

  if ( gridptr->type != GRID_LCC2 )
    Warning("Definition of LCC2 grid for %s grid not allowed!",
	    gridNamePtr(gridptr->type));
  else
    {
      gridptr->lcc2_a       = earth_radius;
      gridptr->lcc2_lon_0   = lon_0;
      gridptr->lcc2_lat_0   = lat_0;
      gridptr->lcc2_lat_1   = lat_1;
      gridptr->lcc2_lat_2   = lat_2;
      gridptr->lcc2_defined = TRUE;
    }
}
