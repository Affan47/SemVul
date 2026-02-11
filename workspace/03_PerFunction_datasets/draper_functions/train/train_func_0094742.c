sim_thread_push(
  thread*         thr,
  const sim_time* time
) { PROFILE(SIM_THREAD_PUSH);

  exp_op_type op;

#ifdef DEBUG_MODE
  if( debug_mode && !flag_use_command_line_debug ) {
    printf( "Before thread is pushed...\n" );
    sim_display_active_queue();
  }
#endif


  thr->suppl.part.state = THR_ST_ACTIVE;


  op = thr->curr->exp->op;
  if( (op == EXP_OP_PEDGE)       ||
      (op == EXP_OP_NEDGE)       ||
      (op == EXP_OP_AEDGE)       ||
      (op == EXP_OP_EOR)         ||
      (op == EXP_OP_WAIT)        ||
      (op == EXP_OP_SLIST)       ||
      (op == EXP_OP_ALWAYS_COMB) ||
      (op == EXP_OP_ALWAYS_LATCH) ) {
    thr->curr_time = *time;
  }


  thr->queue_prev = thr->queue_next = NULL;


  if( active_head == NULL ) {
    active_head = active_tail = thr;
  } else {
    thr->queue_prev         = active_tail;
    active_tail->queue_next = thr;
    active_tail             = thr;
  }

#ifdef DEBUG_MODE
  if( debug_mode && !flag_use_command_line_debug ) {
    printf( "After thread is pushed...\n" );
    sim_display_active_queue();
    sim_display_all_list();
  }
#endif

  PROFILE_END;

}
