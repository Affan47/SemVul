fsm_var_stmt_add(
  statement* stmt,
  char*      funit_name
) { PROFILE(FSM_VAR_STMT_ADD);

  fv_bind* fvb;

  fvb             = (fv_bind*)malloc_safe( sizeof( fv_bind ) );
  fvb->stmt       = stmt;
  fvb->funit_name = strdup_safe( funit_name );
  fvb->next       = NULL;


  if( fsm_var_stmt_head == NULL ) {
    fsm_var_stmt_head = fsm_var_stmt_tail = fvb;
  } else {
    fvb->next         = fsm_var_stmt_head;
    fsm_var_stmt_head = fvb;
  }

  PROFILE_END;

}
