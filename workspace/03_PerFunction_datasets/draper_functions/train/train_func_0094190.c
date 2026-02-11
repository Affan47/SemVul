finish_goto_stmt (tree destination)
{
  if (TREE_CODE (destination) == IDENTIFIER_NODE)
    destination = lookup_label (destination);


  if (TREE_CODE (destination) == LABEL_DECL)
    TREE_USED (destination) = 1;
  else
    {
      destination = mark_rvalue_use (destination);
      if (!processing_template_decl)
	{
	  destination = cp_convert (ptr_type_node, destination,
				    tf_warning_or_error);
	  if (error_operand_p (destination))
	    return NULL_TREE;
	  destination
	    = fold_build_cleanup_point_expr (TREE_TYPE (destination),
					     destination);
	}
    }

  check_goto (destination);

  return add_stmt (build_stmt (input_location, GOTO_EXPR, destination));
}
