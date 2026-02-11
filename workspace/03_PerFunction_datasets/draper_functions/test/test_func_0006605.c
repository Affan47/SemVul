camel_tag_set (CamelTag **list,
               const gchar *name,
               const gchar *value)
{
	CamelTag *tag, *tmp;


	tag = (CamelTag *) list;
	while (tag->next) {
		tmp = tag->next;
		if (!strcmp (tmp->name, name)) {
			if (value == NULL) {
				tag->next = tmp->next;
				g_free (tmp->value);
				g_free (tmp);
				return TRUE;
			} else if (strcmp (tmp->value, value)) {
				g_free (tmp->value);
				tmp->value = g_strdup (value);
				return TRUE;
			}
			return FALSE;
		}
		tag = tmp;
	}

	if (value) {
		tmp = g_malloc (sizeof (*tmp) + strlen (name));
		g_strlcpy (tmp->name, name, strlen (name) + 1);
		tmp->value = g_strdup (value);
		tmp->next = NULL;
		tag->next = tmp;
		return TRUE;
	}
	return FALSE;
}
