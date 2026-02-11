default_binds_local_p_1 (exp, shlib)
     tree exp;
     int shlib;
{
  bool local_p;


  if (!DECL_P (exp))
    local_p = true;

  else if (! TREE_PUBLIC (exp))
    local_p = true;

  else if (decl_visibility (exp) != VISIBILITY_DEFAULT)
    local_p = true;

  else if (DECL_EXTERNAL (exp))
    local_p = false;

  else if (DECL_ONE_ONLY (exp) || DECL_WEAK (exp))
    local_p = false;


  else if (shlib)
    local_p = false;


  else if (DECL_COMMON (exp)
	   && (DECL_INITIAL (exp) == NULL
	       || DECL_INITIAL (exp) == error_mark_node))
    local_p = false;


  else
    local_p = true;

  return local_p;
}
