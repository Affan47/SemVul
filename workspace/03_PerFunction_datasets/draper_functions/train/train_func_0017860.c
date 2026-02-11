assertion_display_verbose(
  FILE*            ofile,
  const func_unit* funit,
  rpt_type         rtype
) { PROFILE(ASSERTION_DISPLAY_VERBOSE);

  switch( rtype ) {
    case RPT_TYPE_HIT  :  fprintf( ofile, "    Hit Assertions\n\n" );       break;
    case RPT_TYPE_MISS :  fprintf( ofile, "    Missed Assertions\n\n" );    break;
    case RPT_TYPE_EXCL :  fprintf( ofile, "    Excluded Assertions\n\n" );  break;
  }


  if( info_suppl.part.assert_ovl == 1 ) {
    ovl_display_verbose( ofile, funit, rtype );
  }

  fprintf( ofile, "\n" );

  PROFILE_END;

}
