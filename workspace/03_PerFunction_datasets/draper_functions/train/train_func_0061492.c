get_action_name(const gchar *entry, gchar **menu)
{
	gchar *act, *act_p;

	*menu = NULL;

	if (prefs_common.actions_list != NULL) {

		act = g_strdup(entry);
		act_p = strstr(act, ": ");
		if (act_p != NULL)
			act_p[0] = 0x00;

		*menu = act;
	}
}
