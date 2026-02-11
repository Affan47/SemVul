check_methods_accessible (tree chain, tree context, int mtype)
{
  int first = 1;
  tree list;
  tree base_context = context;

  while (chain)
    {


      tree x;
      for (x = IMPL_PROPERTY_DECL (base_context); x; x = TREE_CHAIN (x))
	if (PROPERTY_DYNAMIC (x)
	    && (PROPERTY_GETTER_NAME (x) == METHOD_SEL_NAME (chain)
		|| PROPERTY_SETTER_NAME (x) == METHOD_SEL_NAME (chain)))
	  break;

      if (x != NULL_TREE)
	{
	  chain = TREE_CHAIN (chain);
	  continue;
	}

      context = base_context;
      while (context)
	{
	  if (mtype == '+')
	    list = CLASS_CLS_METHODS (context);
	  else
	    list = CLASS_NST_METHODS (context);

	  if (lookup_method (list, chain))
	      break;

	  switch (TREE_CODE (context))
	    {
	    case CLASS_IMPLEMENTATION_TYPE:
	    case CLASS_INTERFACE_TYPE:
	      context = (CLASS_SUPER_NAME (context)
			 ? lookup_interface (CLASS_SUPER_NAME (context))
			 : NULL_TREE);
	      break;
	    case CATEGORY_IMPLEMENTATION_TYPE:
	    case CATEGORY_INTERFACE_TYPE:
	      context = (CLASS_NAME (context)
			 ? lookup_interface (CLASS_NAME (context))
			 : NULL_TREE);
	      break;
	    default:
	      gcc_unreachable ();
	    }
	}

      if (context == NULL_TREE)
	{
	  if (first)
	    {
	      switch (TREE_CODE (objc_implementation_context))
		{
		case CLASS_IMPLEMENTATION_TYPE:
		  warning (0, "incomplete implementation of class %qE",
			   CLASS_NAME (objc_implementation_context));
		  break;
		case CATEGORY_IMPLEMENTATION_TYPE:
		  warning (0, "incomplete implementation of category %qE",
			   CLASS_SUPER_NAME (objc_implementation_context));
		  break;
		default:
		  gcc_unreachable ();
		}
	      first = 0;
	    }
	  warning (0, "method definition for %<%c%E%> not found",
		   mtype, METHOD_SEL_NAME (chain));
	}

      chain = TREE_CHAIN (chain);
    }
  return first;
}
