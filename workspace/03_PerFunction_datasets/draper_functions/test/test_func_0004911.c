e_filter_rule_next_list (GList *list,
                         EFilterRule *last,
                         const gchar *source)
{
	GList *link = list;

	if (last != NULL) {
		link = g_list_find (link, last);
		if (link == NULL)
			link = list;
		else
			link = g_list_next (link);
	}

	if (source != NULL) {
		while (link != NULL) {
			EFilterRule *rule = link->data;

			if (g_strcmp0 (rule->source, source) == 0)
				break;

			link = g_list_next (link);
		}
	}

	return (link != NULL) ? link->data : NULL;
}
