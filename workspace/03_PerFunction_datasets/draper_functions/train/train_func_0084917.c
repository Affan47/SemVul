rw_cfg_read_string (ConfigFile * cfg, gchar * section, gchar * key,
		    gchar ** value)
{
	ConfigSection *sect;
	ConfigLine *line;

	*value = NULL;
	if (!(sect = rw_cfg_find_section (cfg, section)))
		return FALSE;
	if (!(line = rw_cfg_find_string (sect, key)))
		return FALSE;
	*value = g_strdup (line->value);
	return TRUE;
}
