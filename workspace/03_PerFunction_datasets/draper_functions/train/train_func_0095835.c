ResetRoamPoint (tdmInteractor I)
{
  double x, y, z, nx, ny ;
  DEFDATA(I,CursorData) ;

  ENTRY(("ResetRoamPoint(0x%x)", I));

  if (CDATA(view_coords_set))
    {

      x = CDATA(to[0]) - PDATA(Ox) ;
      y = CDATA(to[1]) - PDATA(Oy) ;
      z = CDATA(to[2]) - PDATA(Oz) ;
    }
  else
    {

      x = PDATA(FacetXmax)/2 ;
      y = PDATA(FacetYmax)/2 ;
      z = PDATA(FacetZmax)/2 ;
    }


  XFORM_COORDS(PDATA(Wtrans), x, y, z, nx, ny, PDATA(roam_zbuff)) ;
  PDATA(roam_xbuff) = (int) nx ;
  PDATA(roam_ybuff) = (int) ny ;


  save_cursors_in_canonical_form (I, 0) ;

  PDATA(roam_valid) = 1 ;

  EXIT((""));
}
