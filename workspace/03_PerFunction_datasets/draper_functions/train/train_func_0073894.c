undeclared_variable (tree id)
{
  static bool already = false;
  struct c_scope *scope;

  if (current_function_decl == 0)
    {
      error ("`%s' undeclared here (not in a function)",
	     IDENTIFIER_POINTER (id));
      scope = current_scope;
    }
  else
    {
      error ("`%s' undeclared (first use in this function)",
	     IDENTIFIER_POINTER (id));

      if (! already)
	{
	  error ("(Each undeclared identifier is reported only once");
	  error ("for each function it appears in.)");
	  already = true;
	}

      scope = current_function_scope;
    }

  scope->shadowed = tree_cons (id, IDENTIFIER_SYMBOL_VALUE (id),
			       scope->shadowed);
  IDENTIFIER_SYMBOL_VALUE (id) = error_mark_node;
}
