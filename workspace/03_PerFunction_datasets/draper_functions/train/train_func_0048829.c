get_printer_weave(const stp_vars_t *v)
{
  int i;
  const res_t *res = stp_escp2_find_resolution(v);
  const printer_weave_list_t *p = escp2_printer_weaves(v);
  if (p)
    {
      const char *name = stp_get_string_parameter(v, "Weave");
      int printer_weave_count = p->n_printer_weaves;
      if (name)
	{
	  for (i = 0; i < printer_weave_count; i++)
	    {
	      if (!strcmp(name, p->printer_weaves[i].name))
		return p->printer_weaves[i].command;
	    }
	}
    }
  if (res)
    return res->command;
  return NULL;
}
