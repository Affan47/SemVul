do_per_function (void (*callback) (void *data), void *data)
{
  if (current_function_decl)
    callback (data);
  else
    {
      struct cgraph_node *node;
      FOR_EACH_DEFINED_FUNCTION (node)
	if (gimple_has_body_p (node->symbol.decl)
	    && (!node->clone_of || node->symbol.decl != node->clone_of->symbol.decl))
	  {
	    push_cfun (DECL_STRUCT_FUNCTION (node->symbol.decl));
	    callback (data);
	    if (!flag_wpa)
	      {
	        free_dominance_info (CDI_DOMINATORS);
	        free_dominance_info (CDI_POST_DOMINATORS);
	      }
	    pop_cfun ();
	    ggc_collect ();
	  }
    }
}
