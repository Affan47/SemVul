expression_find_uline_id(
  expression* expr,
  int         ulid
) { PROFILE(EXPRESSION_FIND_ULINE_ID);

  expression* found_exp = NULL;

  if( expr != NULL ) {

    if( expr->ulid == ulid ) {
      found_exp = expr;
    } else {
      if( (found_exp = expression_find_uline_id( expr->left, ulid )) == NULL ) {
        found_exp = expression_find_uline_id( expr->right, ulid );
      }
    }

  }

  PROFILE_END;

  return( found_exp );

}
