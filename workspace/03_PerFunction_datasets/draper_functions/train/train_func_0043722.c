suggest_alternatives_for (location_t location, tree name)
{
  vec<tree> candidates = vNULL;
  vec<tree> namespaces_to_search = vNULL;
  int max_to_search = PARAM_VALUE (CXX_MAX_NAMESPACES_FOR_DIAGNOSTIC_HELP);
  int n_searched = 0;
  tree t;
  unsigned ix;

  namespaces_to_search.safe_push (global_namespace);

  while (!namespaces_to_search.is_empty ()
	 && n_searched < max_to_search)
    {
      tree scope = namespaces_to_search.pop ();
      struct scope_binding binding = EMPTY_SCOPE_BINDING;
      cp_binding_level *level = NAMESPACE_LEVEL (scope);


      qualified_lookup_using_namespace (name, scope, &binding, 0);

      n_searched++;

      if (binding.value)
	candidates.safe_push (binding.value);


      for (t = level->namespaces; t; t = DECL_CHAIN (t))
	namespaces_to_search.safe_push (t);
    }


  if (n_searched >= max_to_search
      && !namespaces_to_search.is_empty ())
    inform (location,
	    "maximum limit of %d namespaces searched for %qE",
	    max_to_search, name);

  namespaces_to_search.release ();


  if (candidates.is_empty ())
    return;

  inform_n (location, candidates.length (),
	    "suggested alternative:",
	    "suggested alternatives:");

  FOR_EACH_VEC_ELT (candidates, ix, t)
    inform (location_of (t), "  %qE", t);

  candidates.release ();
}
