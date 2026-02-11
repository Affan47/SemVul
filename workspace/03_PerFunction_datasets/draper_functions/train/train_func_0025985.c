check_for_loop_decls (location_t loc, bool turn_off_iso_c99_error)
{
  struct c_binding *b;
  tree one_decl = NULL_TREE;
  int n_decls = 0;

  if (!turn_off_iso_c99_error)
    {
      static bool hint = true;


      error_at (loc, "%<for%> loop initial declarations "
		"are only allowed in C99 mode");
      if (hint)
	{
	  inform (loc,
		  "use option -std=c99 or -std=gnu99 to compile your code");
	  hint = false;
	}
      return NULL_TREE;
    }


  for (b = current_scope->bindings; b; b = b->prev)
    {
      tree id = b->id;
      tree decl = b->decl;

      if (!id)
	continue;

      switch (TREE_CODE (decl))
	{
	case VAR_DECL:
	  {
	    location_t decl_loc = DECL_SOURCE_LOCATION (decl);
	    if (TREE_STATIC (decl))
	      error_at (decl_loc,
			"declaration of static variable %qD in %<for%> loop "
			"initial declaration", decl);
	    else if (DECL_EXTERNAL (decl))
	      error_at (decl_loc,
			"declaration of %<extern%> variable %qD in %<for%> loop "
			"initial declaration", decl);
	  }
	  break;

	case RECORD_TYPE:
	  error_at (loc,
		    "%<struct %E%> declared in %<for%> loop initial "
		    "declaration", id);
	  break;
	case UNION_TYPE:
	  error_at (loc,
		    "%<union %E%> declared in %<for%> loop initial declaration",
		    id);
	  break;
	case ENUMERAL_TYPE:
	  error_at (loc, "%<enum %E%> declared in %<for%> loop "
		    "initial declaration", id);
	  break;
	default:
	  error_at (loc, "declaration of non-variable "
		    "%qD in %<for%> loop initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  return n_decls == 1 ? one_decl : NULL_TREE;
}
