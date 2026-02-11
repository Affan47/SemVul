element_start(GMarkupParseContext *context,
				const gchar *element_name,
				const gchar **attribute_names,
				const gchar **attribute_values,
				gpointer user_data, GError **err)
{
	struct context_data *ctx_data = user_data;

	if (!strcmp(element_name, "record"))
		return;

	if (!strcmp(element_name, "attribute")) {
		int i;
		for (i = 0; attribute_names[i]; i++) {
			if (strcmp(attribute_names[i], "id") != 0)
				continue;
			if (strtol(attribute_values[i], 0, 0) == ATTRID_1284ID)
				ctx_data->found = TRUE;
			break;
		}
		return;
	}

	if (ctx_data->found  && !strcmp(element_name, "text")) {
		int i;
		for (i = 0; attribute_names[i]; i++) {
			if (!strcmp(attribute_names[i], "value")) {
				ctx_data->id = g_strdup(attribute_values[i] + 2);
				ctx_data->found = FALSE;
			}
		}
	}
}
