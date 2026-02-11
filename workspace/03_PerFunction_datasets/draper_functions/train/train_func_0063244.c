totem_pl_parser_get_function_for_mimetype (const char *mimetype)
{
	guint i;

	if (mimetype == NULL)
		return NULL;

	for (i = 0; i < G_N_ELEMENTS(special_types); i++) {
		if (strcmp (special_types[i].mimetype, mimetype) == 0)
			return special_types[i].func;
	}
	for (i = 0; i < G_N_ELEMENTS(dual_types); i++) {
		if (strcmp (dual_types[i].mimetype, mimetype) == 0)
			return dual_types[i].func;
	}
	return NULL;
}
