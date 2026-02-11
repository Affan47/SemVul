class_or_namespace_scope_p (dw_die_ref context_die)
{
  return (class_scope_p (context_die)
	  || (context_die && context_die->die_tag == DW_TAG_namespace));
}
