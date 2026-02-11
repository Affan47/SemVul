expand_expr_stmt_value (exp, want_value, maybe_last)
     tree exp;
     int want_value, maybe_last;
{
  rtx value;
  tree type;

  if (want_value == -1)
    want_value = expr_stmts_for_value != 0;


  if (! want_value
      && (expr_stmts_for_value == 0 || ! maybe_last)
      && exp != error_mark_node)
    {
      if (! TREE_SIDE_EFFECTS (exp))
	{
	  if ((extra_warnings || warn_unused_value)
	      && !(TREE_CODE (exp) == CONVERT_EXPR
		   && VOID_TYPE_P (TREE_TYPE (exp))))
	    warning_with_file_and_line (emit_filename, emit_lineno,
				        "statement with no effect");
	}
      else if (warn_unused_value)
	warn_if_unused_value (exp);
    }


  if (want_value && TREE_CODE (TREE_TYPE (exp)) == FUNCTION_TYPE)
    exp = build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (exp)), exp);


  value = expand_expr (exp, want_value ? NULL_RTX : const0_rtx,
		       VOIDmode, 0);
  type = TREE_TYPE (exp);


  if (value && GET_CODE (value) == MEM && TREE_THIS_VOLATILE (exp))
    {
      if (TYPE_MODE (type) == VOIDmode)
	;
      else if (TYPE_MODE (type) != BLKmode)
	value = copy_to_reg (value);
      else
	{
	  rtx lab = gen_label_rtx ();


	  emit_cmp_and_jump_insns (value, value, EQ,
				   expand_expr (TYPE_SIZE (type),
						NULL_RTX, VOIDmode, 0),
				   BLKmode, 0, lab);
	  emit_label (lab);
	}
    }


  preserve_temp_slots (value);


  free_temp_slots ();

  if (want_value)
    {
      last_expr_value = value;
      last_expr_type = type;
    }

  emit_queue ();
}
