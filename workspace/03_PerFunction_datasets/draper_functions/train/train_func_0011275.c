finish_destructor_body (void)
{
  tree exprstmt;


  add_stmt (build_stmt (input_location, LABEL_EXPR, cdtor_label));


  if (DECL_VIRTUAL_P (current_function_decl))
    {
      tree if_stmt;
      tree virtual_size = cxx_sizeof (current_class_type);


      exprstmt = build_op_delete_call (DELETE_EXPR, current_class_ptr,
				       virtual_size,
				       false,
				       NULL_TREE,
				       NULL_TREE,
				       tf_warning_or_error);

      if_stmt = begin_if_stmt ();
      finish_if_stmt_cond (build2 (BIT_AND_EXPR, integer_type_node,
				   current_in_charge_parm,
				   integer_one_node),
			   if_stmt);
      finish_expr_stmt (exprstmt);
      finish_then_clause (if_stmt);
      finish_if_stmt (if_stmt);
    }

  if (targetm.cxx.cdtor_returns_this ())
    {
      tree val;

      val = DECL_ARGUMENTS (current_function_decl);
      val = build2 (MODIFY_EXPR, TREE_TYPE (val),
		    DECL_RESULT (current_function_decl), val);

      exprstmt = build_stmt (input_location, RETURN_EXPR, val);
      add_stmt (exprstmt);
    }
}
