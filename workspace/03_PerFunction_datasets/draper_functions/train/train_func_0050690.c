record_builtin_type (enum rid rid_index,
		     const char* name,
		     tree type)
{
  tree rname = NULL_TREE, tname = NULL_TREE;
  tree tdecl = NULL_TREE;

  if ((int) rid_index < (int) RID_MAX)
    rname = ridpointers[(int) rid_index];
  if (name)
    tname = get_identifier (name);


  if (tname)
    {
      tdecl = build_decl (BUILTINS_LOCATION, TYPE_DECL, tname, type);
      DECL_ARTIFICIAL (tdecl) = 1;
      SET_IDENTIFIER_GLOBAL_VALUE (tname, tdecl);
    }
  if (rname)
    {
      if (!tdecl)
	{
	  tdecl = build_decl (BUILTINS_LOCATION, TYPE_DECL, rname, type);
	  DECL_ARTIFICIAL (tdecl) = 1;
	}
      SET_IDENTIFIER_GLOBAL_VALUE (rname, tdecl);
    }

  if (!TYPE_NAME (type))
    TYPE_NAME (type) = tdecl;

  if (tdecl)
    debug_hooks->type_decl (tdecl, 0);
}
