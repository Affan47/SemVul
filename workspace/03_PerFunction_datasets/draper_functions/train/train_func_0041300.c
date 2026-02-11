lto_symtab_merge (lto_symtab_entry_t prevailing, lto_symtab_entry_t entry)
{
  tree prevailing_decl = prevailing->decl;
  tree decl = entry->decl;
  tree prevailing_type, type;


  TREE_ADDRESSABLE (prevailing_decl) |= TREE_ADDRESSABLE (decl);
  TREE_ADDRESSABLE (decl) |= TREE_ADDRESSABLE (prevailing_decl);


  if (TREE_CODE (decl) == FUNCTION_DECL)
    {
      if (!types_compatible_p (TREE_TYPE (prevailing_decl),
			       TREE_TYPE (decl)))


	(void) 0;

      return true;
    }


  prevailing_type = TYPE_MAIN_VARIANT (TREE_TYPE (prevailing_decl));
  type = TYPE_MAIN_VARIANT (TREE_TYPE (decl));

  if (!types_compatible_p (prevailing_type, type))
    {
      if (COMPLETE_TYPE_P (type))
	return false;


      if (TREE_CODE (prevailing_type) != TREE_CODE (type))
	return false;

      if (TREE_CODE (prevailing_type) == ARRAY_TYPE)
	{
	  tree tem1 = TREE_TYPE (prevailing_type);
	  tree tem2 = TREE_TYPE (type);
	  while (TREE_CODE (tem1) == ARRAY_TYPE
		 && TREE_CODE (tem2) == ARRAY_TYPE)
	    {
	      tem1 = TREE_TYPE (tem1);
	      tem2 = TREE_TYPE (tem2);
	    }

	  if (TREE_CODE (tem1) != TREE_CODE (tem2))
	    return false;

	  if (!types_compatible_p (tem1, tem2))
	    return false;
	}


    }


  if ((DECL_USER_ALIGN (prevailing_decl) && DECL_USER_ALIGN (decl))
      && DECL_ALIGN (prevailing_decl) < DECL_ALIGN (decl))
    return false;

  return true;
}
