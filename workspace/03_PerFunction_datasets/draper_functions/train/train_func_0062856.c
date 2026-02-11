expression_set_tf(
  expression* expr,
  bool        changed
) {


  if( changed || (expr->value->suppl.part.set == 0) ) {


    if( !vector_is_unknown( expr->value ) ) {
      if( vector_is_not_zero( expr->value ) ) {
        expr->suppl.part.true   = 1;
        expr->suppl.part.eval_t = 1;
      } else {
        expr->suppl.part.false  = 1;
        expr->suppl.part.eval_f = 1;
      }
    }


    expr->value->suppl.part.set = 1;

  }

}
