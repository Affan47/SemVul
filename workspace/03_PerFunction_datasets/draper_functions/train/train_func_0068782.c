gen_item_db_write_expr_tree(
  gen_item* gi,
  FILE*     ofile
) { PROFILE(GEN_ITEM_DB_WRITE_EXPR_TREE);


  if( (gi->suppl.part.type == GI_TYPE_STMT) && (gi->suppl.part.removed == 0) ) {

    statement_db_write_expr_tree( gi->elem.stmt, ofile );

  }

  PROFILE_END;

}
