gen_lsm_tmp_name (tree ref)
{
  const char *name;

  switch (TREE_CODE (ref))
    {
    case MEM_REF:
    case TARGET_MEM_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_");
      break;

    case ADDR_EXPR:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      break;

    case BIT_FIELD_REF:
    case VIEW_CONVERT_EXPR:
    case ARRAY_RANGE_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      break;

    case REALPART_EXPR:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_RE");
      break;

    case IMAGPART_EXPR:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_IM");
      break;

    case COMPONENT_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_");
      name = get_name (TREE_OPERAND (ref, 1));
      if (!name)
	name = "F";
      lsm_tmp_name_add (name);
      break;

    case ARRAY_REF:
      gen_lsm_tmp_name (TREE_OPERAND (ref, 0));
      lsm_tmp_name_add ("_I");
      break;

    case SSA_NAME:
    case VAR_DECL:
    case PARM_DECL:
      name = get_name (ref);
      if (!name)
	name = "D";
      lsm_tmp_name_add (name);
      break;

    case STRING_CST:
      lsm_tmp_name_add ("S");
      break;

    case RESULT_DECL:
      lsm_tmp_name_add ("R");
      break;

    case INTEGER_CST:

      break;

    default:
      gcc_unreachable ();
    }
}
