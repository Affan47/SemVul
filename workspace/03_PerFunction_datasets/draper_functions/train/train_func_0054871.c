se_prop_set_bool (se_t *se, se_o_t *o, const char *id, int value)
{
  se_prop_t *p;

  if (!o)
    o = se->g;

  p = se_prop_find (se, o, id);
  if (p)
  {
    se_prop_read_t v;
    if (p->reader && p->se_type != SE_TYPE_BOOL)
    {
      g_printerr (_("script_engine: se_prop_set%s: can't change type of property %s\n"),
	       "_bool", se_id (se, o, id));
      return;
    }
    free (p->value);
    p->value = g_strdup_printf ("%d", v.i = !!value);
    p->se_type = SE_TYPE_BOOL;
    se_prop_listeners (se, o, p, v);
  }
  else
    se_prop_create_bool (se, o, id, value, FALSE);
}
