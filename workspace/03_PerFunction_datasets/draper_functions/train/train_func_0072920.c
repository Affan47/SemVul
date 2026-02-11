arm_function_in_section_p (tree decl, section *section)
{


  if (!TREE_STATIC (decl))
    return false;


  if (!targetm.binds_local_p (decl))
    return false;


  if (!DECL_SECTION_NAME (decl))
    {

      if (flag_function_sections || DECL_ONE_ONLY (decl))
	return false;
    }

  return function_section (decl) == section;
}
