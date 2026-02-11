tcl_func_collect_covered_lines(
  ClientData  d,
  Tcl_Interp* tcl,
  int         argc,
  const char* argv[]
) { PROFILE(TCL_FUNC_COLLECT_COVERED_LINES);

  int        retval  = TCL_OK;
  int*       lines;
  int*       excludes;
  char**     reasons;
  int        line_cnt;
  int        line_size;
  int        i;
  char       str[50];
  func_unit* funit;

  if( (funit = tcl_func_get_funit( tcl, argv[1] )) != NULL ) {

    line_collect( funit, 1, &lines, &excludes, &reasons, &line_cnt, &line_size );

    for( i=0; i<line_cnt; i++ ) {
      snprintf( str, 50, "%d %d {%s}", lines[i], excludes[i], ((reasons[i] != NULL) ? reasons[i] : "") );
      Tcl_AppendElement( tcl, str );
      free_safe( reasons[i], (strlen( reasons[i] ) + 1) );
    }

    free_safe( lines,    (sizeof( int ) * line_size) );
    free_safe( excludes, (sizeof( int ) * line_size) );
    free_safe( reasons,  (sizeof( char* ) * line_size) );

  } else {

    strcpy( user_msg, "Internal Error:  Unable to find functional unit in design" );
    Tcl_AddErrorInfo( tcl, user_msg );
    print_output( user_msg, FATAL, __FILE__, __LINE__ );
    retval = TCL_ERROR;

  }

  return( retval );

}
