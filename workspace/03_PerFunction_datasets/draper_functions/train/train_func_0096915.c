exclude_set_line_exclude(
            func_unit* funit,
            int        line,
            int        value,
            char*      reason,
   statistic* stat
) { PROFILE(EXCLUDE_SET_LINE_EXCLUDE);

  func_iter  fi;
  statement* stmt;

  func_iter_init( &fi, funit, TRUE, FALSE );

  do {
    while( ((stmt = func_iter_get_next_statement( &fi )) != NULL) && (stmt->exp->line != line) );
    if( stmt != NULL ) {

      exclude_expr_assign_and_recalc( stmt->exp, funit, (value == 1), TRUE, stat );


      if( value == 1 ) {
        if( reason != NULL ) {
          exclude_add_exclude_reason( 'L', stmt->exp->id, reason, funit );
        }
      } else {
        exclude_remove_exclude_reason( 'L', stmt->exp->id, funit );
      }

    }
  } while( stmt != NULL );

  func_iter_dealloc( &fi );

  PROFILE_END;

}
