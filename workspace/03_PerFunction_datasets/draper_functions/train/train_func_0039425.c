race_find_head_statement_containing_statement(
  statement* stmt
) { PROFILE(RACE_FIND_HEAD_STATEMENT_CONTAINING_STATEMENT);

  int i = 0;

  while( (i < sb_size) && !race_find_head_statement_containing_statement_helper( sb[i].stmt, stmt ) ) {
    i++;
    stmt_conn_id++;
  }

  if( i < sb_size ) {
    stmt_conn_id++;
  }

  PROFILE_END;

  return( (i == sb_size) ? NULL : sb[i].stmt );

}
