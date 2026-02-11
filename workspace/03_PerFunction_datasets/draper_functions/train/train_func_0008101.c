msole_prop_id_to_gsf (GsfMSOleMetaDataSection *section, guint32 id, gboolean *linked)
{
	char const *res = NULL;
	GsfMSOleMetaDataPropMap const *map = NULL;
	unsigned i = 0;

	*linked = FALSE;
	if (section->dict != NULL) {
		if (id & 0x1000000) {
			*linked = TRUE;
			id &= ~0x1000000;
			d (g_print ("LINKED "););
		}

		res = g_hash_table_lookup (section->dict, GINT_TO_POINTER (id));

		if (res != NULL) {
			d (g_print ("%s", res););
			return res;
		}
	}

	map = builtin_props ;
	i = G_N_ELEMENTS (builtin_props);
	while (i-- > 0)
		if (map[i].id == id &&
		    (map[i].section == COMMON_PROP || map[i].section == section->type)) {
			d (g_print ("%s\n", map[i].gsf_name););
			return map[i].gsf_name;
		}

	d (g_print ("_UNKNOWN_(0x%x %d)\n", id, id););

	return NULL;
}
