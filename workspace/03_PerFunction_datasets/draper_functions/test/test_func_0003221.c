process_subob_fn (tree fn, tree *spec_p, bool *trivial_p,
		  bool *deleted_p, bool *constexpr_p,
		  bool diag, tree arg)
{
  if (!fn || fn == error_mark_node)
    goto bad;

  if (spec_p)
    {
      tree raises = TYPE_RAISES_EXCEPTIONS (TREE_TYPE (fn));
      *spec_p = merge_exception_specifiers (*spec_p, raises, fn);
    }

  if (!trivial_fn_p (fn))
    {
      if (trivial_p)
	*trivial_p = false;
      if (TREE_CODE (arg) == FIELD_DECL
	  && TREE_CODE (DECL_CONTEXT (arg)) == UNION_TYPE)
	{
	  if (deleted_p)
	    *deleted_p = true;
	  if (diag)
	    error ("union member %q+D with non-trivial %qD", arg, fn);
	}
    }

  if (constexpr_p && !DECL_DECLARED_CONSTEXPR_P (fn))
    {
      *constexpr_p = false;
      if (diag)
	{
	  inform (0, "defaulted constructor calls non-constexpr "
		  "%q+D", fn);
	  explain_invalid_constexpr_fn (fn);
	}
    }

  return;

 bad:
  if (deleted_p)
    *deleted_p = true;
}
