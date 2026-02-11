race_calc_expr_assignment(
  expression* exp,
  int         sb_index
) { PROFILE(RACE_CALC_EXPR_ASSIGNMENT);

  switch( exp->op ) {
    case EXP_OP_ASSIGN    :
    case EXP_OP_DASSIGN   :  sb[sb_index].bassign = TRUE;  break;
    case EXP_OP_NASSIGN   :  sb[sb_index].nassign = TRUE;  break;
    case EXP_OP_BASSIGN   :  sb[sb_index].bassign = (exp->suppl.part.for_cntrl == 0);  break;
    case EXP_OP_TASK_CALL :
    case EXP_OP_FORK      :
    case EXP_OP_NB_CALL   :  race_calc_assignments( exp->elem.funit->first_stmt, sb_index );  break;
    default               :  break;
  }

  PROFILE_END;

}
