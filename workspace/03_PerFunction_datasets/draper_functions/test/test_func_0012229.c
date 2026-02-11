prepare_decl_rtl (tree *expr_p, int *ws, void *data)
{
  tree obj = NULL_TREE;
  rtx x = NULL_RTX;
  int *regno = (int *) data;

  switch (TREE_CODE (*expr_p))
    {
    case ADDR_EXPR:
      for (expr_p = &TREE_OPERAND (*expr_p, 0);
	   handled_component_p (*expr_p);
	   expr_p = &TREE_OPERAND (*expr_p, 0))
	continue;
      obj = *expr_p;
      if (DECL_P (obj) && !DECL_RTL_SET_P (obj))
        x = produce_memory_decl_rtl (obj, regno);
      break;

    case SSA_NAME:
      *ws = 0;
      obj = SSA_NAME_VAR (*expr_p);
      if (!DECL_RTL_SET_P (obj))
	x = gen_raw_REG (DECL_MODE (obj), (*regno)++);
      break;

    case VAR_DECL:
    case PARM_DECL:
    case RESULT_DECL:
      *ws = 0;
      obj = *expr_p;

      if (DECL_RTL_SET_P (obj))
	break;

      if (DECL_MODE (obj) == BLKmode)
	x = produce_memory_decl_rtl (obj, regno);
      else
	x = gen_raw_REG (DECL_MODE (obj), (*regno)++);

      break;

    default:
      break;
    }

  if (x)
    {
      VEC_safe_push (tree, heap, decl_rtl_to_reset, obj);
      SET_DECL_RTL (obj, x);
    }

  return NULL_TREE;
}
