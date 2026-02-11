combination_calc_depth(
  expression*  exp,
  unsigned int curr_depth,
  bool         left
) { PROFILE(COMBINATION_CALC_DEPTH);

  int our_depth;

  if( ((report_comb_depth == REPORT_DETAILED) && ((curr_depth + 1) <= report_comb_depth)) ||
       (report_comb_depth == REPORT_VERBOSE) ) {

    if( left ) {

      if( (exp->left != NULL) && (exp->op == exp->left->op) ) {
        our_depth = curr_depth;
      } else {
        our_depth = curr_depth + 1;
      }

    } else {

      if( (exp->right != NULL) && (exp->op == exp->right->op) ) {
        our_depth = curr_depth;
      } else {
        our_depth = curr_depth + 1;
      }

    }

  } else {

    our_depth = curr_depth + 1;

  }

  PROFILE_END;

  return( our_depth );

}
