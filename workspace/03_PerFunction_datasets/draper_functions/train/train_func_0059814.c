rank_gather_expression_cov(
            expression*   exp,
            unsigned int  exclude,
   comp_cdd_cov* comp_cov
) { PROFILE(RANK_GATHER_EXPRESSION_COV);


  if( (exp->suppl.part.root == 1) &&
      (exp->op != EXP_OP_DELAY)   &&
      (exp->op != EXP_OP_CASE)    &&
      (exp->op != EXP_OP_CASEX)   &&
      (exp->op != EXP_OP_CASEZ)   &&
      (exp->op != EXP_OP_DEFAULT) &&
      (exp->op != EXP_OP_NB_CALL) &&
      (exp->op != EXP_OP_FORK)    &&
      (exp->op != EXP_OP_JOIN)    &&
      (exp->op != EXP_OP_NOOP)    &&
      (exp->line != 0) ) {
    uint64 index = comp_cov->cps_index[CP_TYPE_LINE]++;
    rank_check_index( CP_TYPE_LINE, index, __LINE__ );
    if( (exp->exec_num > 0) || exclude ) {
      comp_cov->cps[CP_TYPE_LINE][UL_DIV(index)] |= (ulong)0x1 << UL_MOD(index);
    }
  }


  rank_gather_comb_cov( exp, comp_cov );

  PROFILE_END;

}
