expression_op_func__expand(
               expression*     expr,
   thread*         thr,
   const sim_time* time
) { PROFILE(EXPRESSION_OP_FUNC__EXPAND);


  bool retval = FALSE;

  if( expr->value->width > 0 ) {


    retval = vector_op_expand( expr->value, expr->left->value, expr->right->value );


    expression_set_tf_preclear( expr, retval );
    vector_set_unary_evals( expr->value );
    expression_set_eval_NN( expr );

  }

  PROFILE_END;

  return( retval );

}
