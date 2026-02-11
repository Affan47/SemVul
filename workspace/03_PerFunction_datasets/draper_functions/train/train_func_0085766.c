gen_item_assign_ids(
  gen_item*  gi,
  func_unit* funit
) { PROFILE(GEN_ITEM_ASSIGN_IDS);

  if( gi->suppl.part.removed == 0 ) {


    if( gi->suppl.part.type == GI_TYPE_STMT ) {
      statement_assign_expr_ids( gi->elem.stmt, funit );
    } else if( gi->suppl.part.type == GI_TYPE_SIG ) {
      gi->elem.sig->id = curr_sig_id;
      curr_sig_id++;
    }

  }

  PROFILE_END;

}
