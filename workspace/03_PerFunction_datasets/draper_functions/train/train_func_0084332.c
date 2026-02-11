check_template_keyword (tree decl)
{


  if (TREE_CODE (decl) != TEMPLATE_DECL
      && TREE_CODE (decl) != TEMPLATE_ID_EXPR)
    {
      if (!is_overloaded_fn (decl))
	permerror (input_location, "%qD is not a template", decl);
      else
	{
	  tree fns;
	  fns = decl;
	  if (BASELINK_P (fns))
	    fns = BASELINK_FUNCTIONS (fns);
	  while (fns)
	    {
	      tree fn = OVL_CURRENT (fns);
	      if (TREE_CODE (fn) == TEMPLATE_DECL
		  || TREE_CODE (fn) == TEMPLATE_ID_EXPR)
		break;
	      if (TREE_CODE (fn) == FUNCTION_DECL
		  && DECL_USE_TEMPLATE (fn)
		  && PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (fn)))
		break;
	      fns = OVL_NEXT (fns);
	    }
	  if (!fns)
	    permerror (input_location, "%qD is not a template", decl);
	}
    }
}
