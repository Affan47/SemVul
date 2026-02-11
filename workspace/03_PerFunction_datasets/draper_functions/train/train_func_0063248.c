maybe_apply_renaming_pragma (tree decl, tree asmname)
{
  unsigned ix;
  pending_redefinition *p;


  if ((TREE_CODE (decl) != FUNCTION_DECL && TREE_CODE (decl) != VAR_DECL)
      || (!TREE_PUBLIC (decl) && !DECL_EXTERNAL (decl))
      || !has_c_linkage (decl))
    return asmname;


  if (DECL_ASSEMBLER_NAME_SET_P (decl))
    {
      const char *oldname = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));
      oldname = targetm.strip_name_encoding (oldname);

      if (asmname && strcmp (TREE_STRING_POINTER (asmname), oldname))
	  warning (OPT_Wpragmas, "asm declaration ignored due to "
		   "conflict with previous rename");


      FOR_EACH_VEC_ELT (pending_redefinition, pending_redefine_extname, ix, p)
	if (DECL_NAME (decl) == p->oldname)
	  {

	    if (strcmp (IDENTIFIER_POINTER (p->newname), oldname))
	      warning (OPT_Wpragmas, "#pragma redefine_extname ignored due to "
		       "conflict with previous rename");

	    VEC_unordered_remove (pending_redefinition,
				  pending_redefine_extname, ix);
	    break;
	  }
      return 0;
    }


  FOR_EACH_VEC_ELT (pending_redefinition, pending_redefine_extname, ix, p)
    if (DECL_NAME (decl) == p->oldname)
      {
	tree newname = p->newname;
	VEC_unordered_remove (pending_redefinition,
			      pending_redefine_extname, ix);


	if (asmname)
	  {
	    if (strcmp (TREE_STRING_POINTER (asmname),
			IDENTIFIER_POINTER (newname)) != 0)
	      warning (OPT_Wpragmas, "#pragma redefine_extname ignored due to "
		       "conflict with __asm__ declaration");
	    return asmname;
	  }


	return build_string (IDENTIFIER_LENGTH (newname),
			     IDENTIFIER_POINTER (newname));
      }


  if (asmname)
    return asmname;


  if (pragma_extern_prefix)
    {
      const char *prefix = TREE_STRING_POINTER (pragma_extern_prefix);
      size_t plen = TREE_STRING_LENGTH (pragma_extern_prefix) - 1;

      const char *id = IDENTIFIER_POINTER (DECL_NAME (decl));
      size_t ilen = IDENTIFIER_LENGTH (DECL_NAME (decl));

      char *newname = (char *) alloca (plen + ilen + 1);

      memcpy (newname,        prefix, plen);
      memcpy (newname + plen, id, ilen + 1);

      return build_string (plen + ilen, newname);
    }


  return 0;
}
