get_emit_format(void)
{
  Emit_format_tab *t;

  if ((t = lookup_emit_format_by_format(emit_format)) != NULL)
	return(t->name);

  return(NULL);
}
