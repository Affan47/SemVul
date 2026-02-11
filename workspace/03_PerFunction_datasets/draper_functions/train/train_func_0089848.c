d_exprlist (struct d_info *di)
{
  struct demangle_component *list = NULL;
  struct demangle_component **p = &list;

  if (d_peek_char (di) == 'E')
    {
      d_advance (di, 1);
      return d_make_comp (di, DEMANGLE_COMPONENT_ARGLIST, NULL, NULL);
    }

  while (1)
    {
      struct demangle_component *arg = d_expression (di);
      if (arg == NULL)
	return NULL;

      *p = d_make_comp (di, DEMANGLE_COMPONENT_ARGLIST, arg, NULL);
      if (*p == NULL)
	return NULL;
      p = &d_right (*p);

      if (d_peek_char (di) == 'E')
	{
	  d_advance (di, 1);
	  break;
	}
    }

  return list;
}
