do_compare_and_jump (tree treeop0, tree treeop1, enum rtx_code signed_code,
		     enum rtx_code unsigned_code, rtx if_false_label,
		     rtx if_true_label, int prob)
{
  rtx op0, op1;
  tree type;
  enum machine_mode mode;
  int unsignedp;
  enum rtx_code code;


  op0 = expand_normal (treeop0);
  if (TREE_CODE (treeop0) == ERROR_MARK)
    return;

  op1 = expand_normal (treeop1);
  if (TREE_CODE (treeop1) == ERROR_MARK)
    return;

  type = TREE_TYPE (treeop0);
  mode = TYPE_MODE (type);
  if (TREE_CODE (treeop0) == INTEGER_CST
      && (TREE_CODE (treeop1) != INTEGER_CST
          || (GET_MODE_BITSIZE (mode)
              > GET_MODE_BITSIZE (TYPE_MODE (TREE_TYPE (treeop1))))))
    {


      type = TREE_TYPE (treeop1);
      mode = TYPE_MODE (type);
    }
  unsignedp = TYPE_UNSIGNED (type);
  code = unsignedp ? unsigned_code : signed_code;

#ifdef HAVE_canonicalize_funcptr_for_compare


  if (HAVE_canonicalize_funcptr_for_compare
      && TREE_CODE (TREE_TYPE (treeop0)) == POINTER_TYPE
      && TREE_CODE (TREE_TYPE (TREE_TYPE (treeop0)))
          == FUNCTION_TYPE
      && TREE_CODE (TREE_TYPE (treeop1)) == POINTER_TYPE
      && TREE_CODE (TREE_TYPE (TREE_TYPE (treeop1)))
          == FUNCTION_TYPE)
    {
      rtx new_op0 = gen_reg_rtx (mode);
      rtx new_op1 = gen_reg_rtx (mode);

      emit_insn (gen_canonicalize_funcptr_for_compare (new_op0, op0));
      op0 = new_op0;

      emit_insn (gen_canonicalize_funcptr_for_compare (new_op1, op1));
      op1 = new_op1;
    }
#endif

  do_compare_rtx_and_jump (op0, op1, code, unsignedp, mode,
                           ((mode == BLKmode)
                            ? expr_size (treeop0) : NULL_RTX),
			   if_false_label, if_true_label, prob);
}
