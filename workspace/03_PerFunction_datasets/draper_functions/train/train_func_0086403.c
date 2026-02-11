db_create_statement(
  expression*  exp,
  unsigned int ppline
) { PROFILE(DB_CREATE_STATEMENT);

  statement* stmt = NULL;


  if( exp != NULL ) {

#ifdef DEBUG_MODE
    if( debug_mode ) {
      unsigned int rv = snprintf( user_msg, USER_MSG_LENGTH, "In db_create_statement, id: %d, line: %d", exp->id, exp->line );
      assert( rv < USER_MSG_LENGTH );
      print_output( user_msg, DEBUG, __FILE__, __LINE__ );
    }
#endif


    stmt = statement_create( exp, curr_funit, ppline );


    if( exclude_mode > 0 ) {
      stmt->suppl.part.excluded = 1;
    }


    if( ignore_racecheck_mode > 0 ) {
      stmt->suppl.part.ignore_rc = 1;
    }

    Try {


      stmt = db_parallelize_statement( stmt );

    } Catch_anonymous {
      statement_dealloc( stmt );
      expression_dealloc( exp, FALSE );
      Throw 0;
    }

  }

  PROFILE_END;

  return( stmt );

}
