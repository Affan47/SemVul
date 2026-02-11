d_template_param (di)
     struct d_info *di;
{
  long param;

  if (d_next_char (di) != 'T')
    return NULL;

  if (d_peek_char (di) == '_')
    param = 0;
  else
    {
      param = d_number (di);
      if (param < 0)
	return NULL;
      param += 1;
    }

  if (d_next_char (di) != '_')
    return NULL;

  ++di->did_subs;

  return d_make_template_param (di, param);
}
