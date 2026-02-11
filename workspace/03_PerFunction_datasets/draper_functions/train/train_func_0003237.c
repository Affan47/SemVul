build_ref_for_model (location_t loc, tree base, HOST_WIDE_INT offset,
		     struct access *model, gimple_stmt_iterator *gsi,
		     bool insert_after)
{
  if (TREE_CODE (model->expr) == COMPONENT_REF
      && DECL_BIT_FIELD (TREE_OPERAND (model->expr, 1)))
    {

      tree t, exp_type, fld = TREE_OPERAND (model->expr, 1);

      offset -= int_bit_position (fld);
      exp_type = TREE_TYPE (TREE_OPERAND (model->expr, 0));
      t = build_ref_for_offset (loc, base, offset, exp_type, gsi, insert_after);
      return fold_build3_loc (loc, COMPONENT_REF, TREE_TYPE (fld), t, fld,
			      NULL_TREE);
    }
  else
    return build_ref_for_offset (loc, base, offset, model->type,
				 gsi, insert_after);
}
