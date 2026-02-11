write_template_param (const tree parm)
{
  int parm_index;
  int parm_level;
  tree parm_type = NULL_TREE;

  MANGLE_TRACE_TREE ("template-parm", parm);

  switch (TREE_CODE (parm))
    {
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
      parm_index = TEMPLATE_TYPE_IDX (parm);
      parm_level = TEMPLATE_TYPE_LEVEL (parm);
      break;

    case TEMPLATE_PARM_INDEX:
      parm_index = TEMPLATE_PARM_IDX (parm);
      parm_level = TEMPLATE_PARM_LEVEL (parm);
      parm_type = TREE_TYPE (TEMPLATE_PARM_DECL (parm));
      break;

    default:
      abort ();
    }

  write_char ('T');


  if (parm_index > 0)
    write_unsigned_number (parm_index - 1);
  write_char ('_');
}
