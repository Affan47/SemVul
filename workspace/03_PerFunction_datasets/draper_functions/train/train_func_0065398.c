egg_recent_item_in_group (const EggRecentItem *item, const gchar *group_name)
{
	GList *tmp;

	tmp = item->groups;
	while (tmp != NULL) {
		gchar *val = (gchar *)tmp->data;

		if (strcmp (group_name, val) == 0)
			return TRUE;

		tmp = tmp->next;
	}

	return FALSE;
}
