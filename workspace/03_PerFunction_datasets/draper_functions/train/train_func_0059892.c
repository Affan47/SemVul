notice_global_symbol (tree decl)
{
  const char **type = &first_global_object_name;

  if (first_global_object_name
      || !TREE_PUBLIC (decl) || DECL_EXTERNAL (decl)
      || !DECL_NAME (decl)
      || (TREE_CODE (decl) != FUNCTION_DECL
	  && (TREE_CODE (decl) != VAR_DECL
	      || (DECL_COMMON (decl)
		  && (DECL_INITIAL (decl) == 0
		      || DECL_INITIAL (decl) == error_mark_node))))
      || GET_CODE (DECL_RTL (decl)) != MEM)
    return;


  if (DECL_WEAK (decl) || DECL_ONE_ONLY (decl))
    type = &weak_global_object_name;

  if (!*type)
    {
      const char *p;
      char *name;
      rtx decl_rtl = DECL_RTL (decl);

      p = (* targetm.strip_name_encoding) (XSTR (XEXP (decl_rtl, 0), 0));
      name = xstrdup (p);

      *type = name;
    }
}
