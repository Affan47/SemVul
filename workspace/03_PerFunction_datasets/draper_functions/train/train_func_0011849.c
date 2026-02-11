xsh_pfits_get_nod_reloffset( const cpl_propertylist * plist)
{
  double returnvalue = 0. ;
  double dec = 0., ra = 0. ;

  check_msg (xsh_get_property_value (plist, XSH_NOD_RELATIVE_OFFSET_DEC,
				     CPL_TYPE_DOUBLE, &dec),
	     "Error reading keyword '%s'", XSH_NOD_RELATIVE_OFFSET_DEC ) ;
  check_msg (xsh_get_property_value (plist, XSH_NOD_RELATIVE_OFFSET_RA,
				     CPL_TYPE_DOUBLE, &ra),
	     "Error reading keyword '%s'", XSH_NOD_RELATIVE_OFFSET_RA ) ;
  returnvalue = sqrt( dec*dec + ra*ra ) ;
  xsh_msg_dbg_high( "dec: %lf, ra: %lf, reloffset: %lf", dec, ra, returnvalue ) ;

 cleanup:
  return returnvalue;
}
