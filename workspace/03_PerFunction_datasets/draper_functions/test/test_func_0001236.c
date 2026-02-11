determine_hidden_inline (tree decl)
{
  return (visibility_options.inlines_hidden


	  && !processing_template_decl
	  && TREE_CODE (decl) == FUNCTION_DECL
	  && DECL_DECLARED_INLINE_P (decl)
	  && (! DECL_LANG_SPECIFIC (decl)
	      || ! DECL_EXPLICIT_INSTANTIATION (decl)));
}
