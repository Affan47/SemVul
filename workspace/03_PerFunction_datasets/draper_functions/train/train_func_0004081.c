outer_binding (tree name,
	       cxx_binding *binding,
	       bool class_p)
{
  cxx_binding *outer;
  cp_binding_level *scope;
  cp_binding_level *outer_scope;

  if (binding)
    {
      scope = binding->scope->level_chain;
      outer = binding->previous;
    }
  else
    {
      scope = current_binding_level;
      outer = IDENTIFIER_BINDING (name);
    }
  outer_scope = outer ? outer->scope : NULL;


  if (class_p)
    while (scope && scope != outer_scope && scope->kind != sk_namespace)
      {
	if (scope->kind == sk_class)
	  {
	    cxx_binding *class_binding;

	    class_binding = get_class_binding (name, scope);
	    if (class_binding)
	      {


		class_binding->previous = outer;
		if (binding)
		  binding->previous = class_binding;
		else
		  IDENTIFIER_BINDING (name) = class_binding;
		return class_binding;
	      }
	  }


	if (outer_scope && outer_scope->kind == sk_template_parms
	    && binding_to_template_parms_of_scope_p (outer, scope))
	  return outer;

	scope = scope->level_chain;
      }

  return outer;
}
