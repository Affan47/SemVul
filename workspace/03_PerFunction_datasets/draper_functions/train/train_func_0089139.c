inline_needs_template_parms (tree decl)
{
  if (! DECL_TEMPLATE_INFO (decl))
    return 0;

  return (TMPL_PARMS_DEPTH (DECL_TEMPLATE_PARMS (most_general_template (decl)))
	  > (processing_template_decl + DECL_TEMPLATE_SPECIALIZATION (decl)));
}
