message_db_read(
  char** line
) { PROFILE(MESSAGE_DB_READ);


  if( (cdd_message == NULL) && (strlen( *line + 1 ) > 0) ) {
    cdd_message = strdup_safe( *line + 1 );
  }

  PROFILE_END;

}
