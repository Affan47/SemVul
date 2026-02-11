se_prop_get_int (se_t *se, se_o_t *o, const char *id)
{
  if (!o)
    o = se->g;

  se_prop_t *p = se_prop_find (se, o, id);
  if (!p)
  {
    g_printerr (_("script_engine: se_prop_get%s error: property %s doesn't exist\n"),
	     "_int", se_id (se, o, id));
    return 0;
  }

  logprintf ("script_engine: getting value of %s=='%s'\n",
	     se_id (se, o, id), p->value);

  switch (p->se_type)
  {
  case SE_TYPE_INT:
    return get_prop_int (se, o, p);

  case SE_TYPE_DOUBLE:
    return floor (get_prop_double (se, o, p));

  case SE_TYPE_BOOL:
    return get_prop_bool (se, o, p);

  default:
    g_printerr (_("script_engine: se_prop_get%s error: %s is not numeric\n"),
	     "_int", se_id (se, o, id));
  }
  return 0;
}
