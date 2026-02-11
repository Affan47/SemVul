decl_anon_ns_mem_p (const_tree decl)
{
  while (1)
    {
      if (decl == NULL_TREE || decl == error_mark_node)
	return false;
      if (TREE_CODE (decl) == NAMESPACE_DECL
	  && DECL_NAME (decl) == NULL_TREE)
	return true;


      else if (TYPE_P (decl))
	return (TREE_PUBLIC (TYPE_MAIN_DECL (decl)) == 0);
      else if (TREE_CODE (decl) == NAMESPACE_DECL)
	return (TREE_PUBLIC (decl) == 0);
      else
	decl = DECL_CONTEXT (decl);
    }
}
