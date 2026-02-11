e2_menu_add_toggle (GtkWidget *menu, gchar *label, gchar *icon,
	gchar *tip, gchar *type, gchar *cmd)
{
	static gboolean first = TRUE;
	static gboolean firststate;
	static gchar *firstlabel;
	static gchar *firsticon;
	static gchar *firsttip;
	static gchar *firstcmd;
	if (label == NULL) label = "";
	if (icon == NULL) icon = "";
	if (tip == NULL) tip = "";
	if (cmd == NULL) cmd = "";
	if (first)
	{
		first = FALSE;

		firststate = g_str_has_suffix (type, _A(111));
		firstlabel = g_strdup (label);
		firsticon = g_strdup (icon);
		firsttip = g_strdup (tip);
		firstcmd = g_strdup (cmd);
		return NULL;
	}

	first = TRUE;

	gchar *hashkey = g_strconcat (firstcmd, ".", cmd, NULL);

	E2_ToggleData *data = g_hash_table_lookup (toggles_hash, hashkey);
	if (data == NULL)
	{
		data = ALLOCATE (E2_ToggleData);
		CHECKALLOCATEDFATAL (data);
		g_hash_table_insert (toggles_hash, g_strdup (hashkey), data);
		data->current_state = firststate;
		data->boxes = NULL;
		if (firststate)
		{
			data->true_action = firstcmd;
			data->false_action = g_strdup (cmd);
		}
		else
		{
			data->false_action = firstcmd;
			data->true_action = g_strdup (cmd);
		}
	}

	gchar *uselabel, *useicon, *usetip;
	if (data->current_state == firststate)
	{
		uselabel = firstlabel;
		useicon = firsticon;
		usetip = firsttip;
	}
	else
	{
		uselabel = label;
		useicon = icon;
		usetip = tip;
	}
	gchar *realarg;
	E2_Action *action = e2_action_get_with_custom (type, cmd, &realarg);
	E2_ActionRuntime *actionrt = e2_action_pack_runtime (action, hashkey, g_free);
	GtkWidget *item = e2_menu_add (menu, uselabel, useicon, usetip,
				e2_action_run, actionrt);
	g_object_set_data_full (G_OBJECT (item), "free-callback-data", actionrt,
		(GDestroyNotify) e2_action_free_runtime);

	g_free (firstlabel);
	g_free (firsticon);
	g_free (firsttip);
	g_free (realarg);

	return item;
}
