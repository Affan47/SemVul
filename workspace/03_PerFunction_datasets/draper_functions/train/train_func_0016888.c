do_range_for_auto_deduction (tree decl, tree range_expr)
{
  tree auto_node = type_uses_auto (TREE_TYPE (decl));
  if (auto_node)
    {
      tree begin_dummy, end_dummy, range_temp, iter_type, iter_decl;
      range_temp = convert_from_reference (build_range_temp (range_expr));
      iter_type = (cp_parser_perform_range_for_lookup
		   (range_temp, &begin_dummy, &end_dummy));
      iter_decl = build_decl (input_location, VAR_DECL, NULL_TREE, iter_type);
      iter_decl = build_x_indirect_ref (input_location, iter_decl, RO_NULL,
					tf_warning_or_error);
      TREE_TYPE (decl) = do_auto_deduction (TREE_TYPE (decl),
					    iter_decl, auto_node);
    }
}
