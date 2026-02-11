db_parallelize_statement(
  statement* stmt
) { PROFILE(DB_PARALLELIZE_STATEMENT);

  expression* exp;
  char*       scope;


  if( (stmt != NULL) && (fork_depth != -1) && (fork_block_depth[fork_depth] == block_depth) ) {

#ifdef DEBUG_MODE
    if( debug_mode ) {
      unsigned int rv = snprintf( user_msg, USER_MSG_LENGTH, "In db_parallelize_statement, id: %d, %s, line: %d, fork_depth: %d, block_depth: %d, fork_block_depth: %d",
                                  stmt->exp->id, expression_string_op( stmt->exp->op ), stmt->exp->line, fork_depth, block_depth, fork_block_depth[fork_depth] );
      assert( rv < USER_MSG_LENGTH );
      print_output( user_msg, DEBUG, __FILE__, __LINE__ );
    }
#endif


    exp = db_create_expression( NULL, NULL, EXP_OP_FORK, FALSE, stmt->exp->line, stmt->exp->col.part.first, stmt->exp->col.part.last, NULL );


    scope = db_create_unnamed_scope();
    if( db_add_function_task_namedblock( FUNIT_NAMED_BLOCK, scope, curr_funit->filename, stmt->exp->line ) ) {


      stmt->suppl.part.head      = 1;
      stmt->suppl.part.is_called = 1;
      db_add_statement( stmt, stmt );


      exp->elem.funit      = curr_funit;
      exp->suppl.part.type = ETYPE_FUNIT;
      exp->name            = strdup_safe( scope );


      db_end_function_task_namedblock( stmt->exp->line );

    }
    free_safe( scope, (strlen( scope ) + 1) );


    fork_depth--;
    block_depth--;

    Try {


      stmt = db_create_statement( exp, stmt->ppline );

    } Catch_anonymous {
      expression_dealloc( exp, FALSE );
      Throw 0;
    }


    fork_depth++;
    block_depth++;

  }

  PROFILE_END;

  return( stmt );

}
