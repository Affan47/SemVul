tcl_func_get_inst_scope(
  ClientData  d,
  Tcl_Interp* tcl,
  int         argc,
  const char* argv[]
) { PROFILE(TCL_FUNC_INST_SCOPE);

  int          retval = TCL_OK;
  func_unit*   funit;
  int          targc;
  const char** targv;

  if( Tcl_SplitList( tcl, argv[1], &targc, &targv ) == TCL_OK ) {
    if( argc == 2 ) {
      char scope[4096];


      scope[0] = '\0';
      instance_gen_scope( scope, gui_inst_list[ atoi( targv[0] ) ], FALSE );
      Tcl_SetResult( tcl, scope, TCL_VOLATILE );
    }
    Tcl_Free( (char*)targv );
  } else {
    strcpy( user_msg, "Internal Error:  Unable to find specified functional unit instance" );
    Tcl_AddErrorInfo( tcl, user_msg );
    print_output( user_msg, FATAL, __FILE__, __LINE__ );
    retval = TCL_ERROR;
  }

  PROFILE_END;

  return( retval );

}
