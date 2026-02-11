lang_decl_name (tree decl, int v, bool translate)
{
  if (v >= 2)
    return (translate
	    ? decl_as_string_translate (decl, TFF_DECL_SPECIFIERS)
	    : decl_as_string (decl, TFF_DECL_SPECIFIERS));

  reinit_cxx_pp ();
  pp_translate_identifiers (cxx_pp) = translate;
  if (v == 1
      && (DECL_CLASS_SCOPE_P (decl)
	  || (DECL_NAMESPACE_SCOPE_P (decl)
	      && CP_DECL_CONTEXT (decl) != global_namespace)))
    {
      dump_type (CP_DECL_CONTEXT (decl), TFF_PLAIN_IDENTIFIER);
      pp_cxx_colon_colon (cxx_pp);
    }

  if (TREE_CODE (decl) == FUNCTION_DECL)
    dump_function_name (decl, TFF_PLAIN_IDENTIFIER);
  else if ((DECL_NAME (decl) == NULL_TREE)
           && TREE_CODE (decl) == NAMESPACE_DECL)
    dump_decl (decl, TFF_PLAIN_IDENTIFIER | TFF_UNQUALIFIED_NAME);
  else
    dump_decl (DECL_NAME (decl), TFF_PLAIN_IDENTIFIER);

  return pp_formatted_text (cxx_pp);
}
