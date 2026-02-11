pan_item_find_by_path_l(GList *list, GList *search_list,
				      PanItemType type, const gchar *path,
				      gboolean ignore_case, gboolean partial)
{
	GList *work;

	work = g_list_last(search_list);
	while (work)
		{
		PanItem *pi;

		pi = work->data;
		if ((pi->type == type || type == PAN_ITEM_NONE) && pi->fd)
			{
			gboolean match = FALSE;

			if (path[0] == G_DIR_SEPARATOR)
				{
				if (pi->fd->path && strcmp(path, pi->fd->path) == 0) match = TRUE;
				}
			else if (pi->fd->name)
				{
				if (partial)
					{
					if (ignore_case)
						{
						gchar *haystack;

						haystack = g_utf8_strdown(pi->fd->name, -1);
						match = (strstr(haystack, path) != NULL);
						g_free(haystack);
						}
					else
						{
						if (strstr(pi->fd->name, path)) match = TRUE;
						}
					}
				else if (ignore_case)
					{
					if (g_ascii_strcasecmp(path, pi->fd->name) == 0) match = TRUE;
					}
				else
					{
					if (strcmp(path, pi->fd->name) == 0) match = TRUE;
					}
				}

			if (match) list = g_list_prepend(list, pi);
			}
		work = work->prev;
		}

	return list;
}
