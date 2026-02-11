finish_handler_parms (tree decl, tree handler)
{
  tree type = NULL_TREE;
  if (processing_template_decl)
    {
      if (decl)
	{
	  decl = pushdecl (decl);
	  decl = push_template_decl (decl);
	  HANDLER_PARMS (handler) = decl;
	  type = TREE_TYPE (decl);
	}
    }
  else
    type = expand_start_catch_block (decl);
  HANDLER_TYPE (handler) = type;
  if (!processing_template_decl && type)
    mark_used (eh_type_info (type));
}
