egg_recent_model_string_match (const GSList *list, const gchar *str)
{
	const GSList *tmp;

	if (list == NULL || str == NULL)
		return TRUE;

	tmp = list;

	while (tmp) {
		if (g_pattern_match_string (tmp->data, str))
			return TRUE;

		tmp = tmp->next;
	}

	return FALSE;
}
