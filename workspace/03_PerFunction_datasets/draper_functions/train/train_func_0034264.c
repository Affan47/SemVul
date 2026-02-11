careful_append (VeSection *section, VeLine *line)
{
	GList *li;
	VeLine *ll;
	gboolean seen_white = FALSE;

	g_assert (line->type == VE_LINE_KEY);

	li = find_commented_out (section, line);
	if (li != NULL) {
		if (li->next == NULL)
			section->lines = g_list_append
				(section->lines, line);
		else
			section->lines = g_list_insert_before
				(section->lines,
				 li->next, line);

		return;
	}

	li = g_list_last (section->lines);
	while (li != NULL) {
		ll = li->data;

		if (ll->type == VE_LINE_TEXT) {
			if (ll->string[0] == '\0') {
				seen_white = TRUE;
			} else if (seen_white) {
				section->lines = g_list_insert_before
					(section->lines,
					 li->next, line);
				return;
			}
		} else {
			if (li->next == NULL)
				section->lines = g_list_append
					(section->lines, line);
			else
				section->lines = g_list_insert_before
					(section->lines,
					 li->next, line);
			return;
		}
		li = li->prev;
	}

	section->lines = g_list_prepend (section->lines, line);
}
