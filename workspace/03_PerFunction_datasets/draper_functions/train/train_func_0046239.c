odf_config_item_end (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	GHashTable *parent_hash;

	if (state->settings.stack == NULL)
		parent_hash = state->settings.settings;
	else
		parent_hash = state->settings.stack->data;

	if (parent_hash != NULL && state->settings.config_item_name != NULL) {
		GValue *val = NULL;
		switch (state->settings.type) {
		case G_TYPE_BOOLEAN: {
			gboolean b = (g_ascii_strcasecmp (xin->content->str, "false") &&
				      strcmp (xin->content->str, "0"));
			val = g_value_init (g_new0 (GValue, 1), G_TYPE_BOOLEAN);
			g_value_set_boolean (val, b);
			break;
		}
		case G_TYPE_INT: {
			long n;
			char *end;

			errno = 0;
			n = strtol (xin->content->str, &end, 10);
			if (!(*end || errno != 0 || n < INT_MIN || n > INT_MAX)) {
				val = g_value_init (g_new0 (GValue, 1), G_TYPE_INT);
				g_value_set_int (val, (int)n);
			}
			break;
		}
		case G_TYPE_LONG: {
			long n;
			char *end;

			errno = 0;
			n = strtol (xin->content->str, &end, 10);
			if (!(*end || errno != 0)) {
				val = g_value_init (g_new0 (GValue, 1), G_TYPE_LONG);
				g_value_set_long (val, n);
			}
			break;
		}
		case G_TYPE_STRING:
			val = g_value_init (g_new0 (GValue, 1), G_TYPE_STRING);
			g_value_set_string (val, (xin->content->str));
			break;
		default:
			break;
		}
		if (val != NULL)
			g_hash_table_replace
				(parent_hash, g_strdup (state->settings.config_item_name),
				 val);
	}

	g_free (state->settings.config_item_name);
	state->settings.config_item_name = NULL;
}
