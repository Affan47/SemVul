c_dump_tree (void *dump_info, tree t)
{
  enum tree_code code;
  dump_info_p di = (dump_info_p) dump_info;


  code = TREE_CODE (t);

  switch (code)
    {
    case FIELD_DECL:
      if (DECL_C_BIT_FIELD (t))
	dump_string (di, "bitfield");
      break;

    default:
      break;
    }

  return false;
}
