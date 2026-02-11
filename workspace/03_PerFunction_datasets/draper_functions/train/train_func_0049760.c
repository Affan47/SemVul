expand_end_stmt_expr (tree t)
{
  OK_DEFER_POP;

  if (! last_expr_value || ! last_expr_type)
    {
      last_expr_value = const0_rtx;
      last_expr_alt_rtl = NULL_RTX;
      last_expr_type = void_type_node;
    }
  else if (GET_CODE (last_expr_value) != REG && ! CONSTANT_P (last_expr_value))

    last_expr_value = protect_from_queue (last_expr_value, 0);

  emit_queue ();

  TREE_TYPE (t) = last_expr_type;
  RTL_EXPR_RTL (t) = last_expr_value;
  RTL_EXPR_ALT_RTL (t) = last_expr_alt_rtl;
  RTL_EXPR_SEQUENCE (t) = get_insns ();

  rtl_expr_chain = tree_cons (NULL_TREE, t, rtl_expr_chain);

  end_sequence ();


  TREE_SIDE_EFFECTS (t) = 1;

  TREE_THIS_VOLATILE (t) = volatile_refs_p (last_expr_value);

  clear_last_expr ();
  expr_stmts_for_value--;

  return t;
}
