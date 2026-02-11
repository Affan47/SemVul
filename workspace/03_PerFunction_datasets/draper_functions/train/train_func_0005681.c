get_binfo_at_offset (tree binfo, HOST_WIDE_INT offset, tree expected_type)
{
  tree type = BINFO_TYPE (binfo);

  while (true)
    {
      HOST_WIDE_INT pos, size;
      tree fld;
      int i;

      if (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (expected_type))
	  return binfo;
      if (offset < 0)
	return NULL_TREE;

      for (fld = TYPE_FIELDS (type); fld; fld = DECL_CHAIN (fld))
	{
	  if (TREE_CODE (fld) != FIELD_DECL)
	    continue;

	  pos = int_bit_position (fld);
	  size = tree_low_cst (DECL_SIZE (fld), 1);
	  if (pos <= offset && (pos + size) > offset)
	    break;
	}
      if (!fld || TREE_CODE (TREE_TYPE (fld)) != RECORD_TYPE)
	return NULL_TREE;

      if (!DECL_ARTIFICIAL (fld))
	{
	  binfo = TYPE_BINFO (TREE_TYPE (fld));
	  if (!binfo)
	    return NULL_TREE;
	}


      else if (offset != 0)
	{
	  tree base_binfo, found_binfo = NULL_TREE;
	  for (i = 0; BINFO_BASE_ITERATE (binfo, i, base_binfo); i++)
	    if (TREE_TYPE (base_binfo) == TREE_TYPE (fld))
	      {
		found_binfo = base_binfo;
		break;
	      }
	  if (!found_binfo)
	    return NULL_TREE;
	  binfo = found_binfo;
	}

      type = TREE_TYPE (fld);
      offset -= pos;
    }
}
