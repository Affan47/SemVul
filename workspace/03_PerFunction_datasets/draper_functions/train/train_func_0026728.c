e_filter_part_find_list (GList *list,
                         const gchar *name)
{
	GList *link;

	g_return_val_if_fail (name != NULL, NULL);

	for (link = list; link != NULL; link = g_list_next (link)) {
		EFilterPart *part = link->data;

		if (g_strcmp0 (part->name, name) == 0)
			return part;
	}

	return NULL;
}
