glade_parameter_get_string (GList *parameters, const gchar *key, gchar **value)
{
	GladeParameter *parameter;
	GList *list;

	list = parameters;
	for (; list != NULL; list = list->next) {
		parameter = list->data;
		if (strcmp (key, parameter->key) == 0) {
			if (*value != NULL)
				g_free (*value);
			*value = g_strdup (parameter->value);
			return;
		}
	}
}
