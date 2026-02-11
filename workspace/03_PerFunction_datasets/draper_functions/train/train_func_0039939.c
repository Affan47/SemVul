expression_op_func__trigger(
  expression*     expr,
  thread*         thr,
  const sim_time* time
) { PROFILE(EXPRESSION_OP_FUNC__TRIGGER);


  expr->sig->value->value.ul[0][VTYPE_INDEX_SIG_VALL] = 1;
  expr->sig->value->value.ul[0][VTYPE_INDEX_SIG_VALH] = 0;


  vsignal_propagate( expr->sig, ((thr == NULL) ? time : &(thr->curr_time)) );

  PROFILE_END;

  return( TRUE );

}
