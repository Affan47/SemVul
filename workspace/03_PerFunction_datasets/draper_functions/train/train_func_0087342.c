objc_build_message_expr (tree receiver, tree message_args)
{
  tree sel_name;
#ifdef OBJCPLUS
  tree args = TREE_PURPOSE (message_args);
#else
  tree args = message_args;
#endif
  tree method_params = NULL_TREE;

  if (TREE_CODE (receiver) == ERROR_MARK || TREE_CODE (args) == ERROR_MARK)
    return error_mark_node;


  switch (TREE_CODE (args))
    {
    case IDENTIFIER_NODE:

      sel_name = args;
      break;
    case TREE_LIST:
      sel_name = build_keyword_selector (args);
      break;
    default:
      gcc_unreachable ();
    }


  if (TREE_CODE (args) == TREE_LIST)
#ifdef OBJCPLUS
    method_params = chainon (args, TREE_VALUE (message_args));
#else
    {
      tree chain = args, prev = NULL_TREE;


      while (chain)
	{
	  tree element = TREE_VALUE (chain);


	  if (TREE_CODE (element) == TREE_LIST)
	    {
	      if (prev)
		TREE_CHAIN (prev) = element;
	      else
		args = element;
	    }
	  prev = chain;
	  chain = TREE_CHAIN (chain);
        }
      method_params = args;
    }
#endif

#ifdef OBJCPLUS
  if (processing_template_decl)

    return build_min_nt_loc (UNKNOWN_LOCATION, MESSAGE_SEND_EXPR, receiver,
			     sel_name, method_params);
#endif

  return objc_finish_message_expr (receiver, sel_name, method_params, NULL);
}
