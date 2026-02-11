default_select_section (tree decl, int reloc,
			unsigned HOST_WIDE_INT align ATTRIBUTE_UNUSED)
{
  if (DECL_P (decl))
    {
      if (decl_readonly_section (decl, reloc))
	return readonly_data_section;
    }
  else if (TREE_CODE (decl) == CONSTRUCTOR)
    {
      if (! ((flag_pic && reloc)
	     || !TREE_READONLY (decl)
	     || TREE_SIDE_EFFECTS (decl)
	     || !TREE_CONSTANT (decl)))
	return readonly_data_section;
    }
  else if (TREE_CODE (decl) == STRING_CST)
    return readonly_data_section;
  else if (! (flag_pic && reloc))
    return readonly_data_section;

  return data_section;
}
