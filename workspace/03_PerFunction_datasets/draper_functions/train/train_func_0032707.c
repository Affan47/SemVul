se_prop_set_reader_func (se_t *se, se_o_t *o, const char *id,
			      se_prop_reader_t reader)
{
  se_prop_t *p;

  if (!o)
    o = se->g;

  logprintf ("script_engine: setting reader for %s\n", se_id (se, o, id));

  p = se_prop_find (se, o, id);
  if (!p)
    g_printerr (_("script_engine: error in %s: property %s not found\n"),
	     __func__, se_id (se, o, id));
  else
    p->reader = reader;
}
