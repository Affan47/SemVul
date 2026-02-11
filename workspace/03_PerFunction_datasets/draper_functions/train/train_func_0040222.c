menu_setting_foreach (void (*callback) (session *), int id, guint state)
{
	session *sess;
	GSList *list;
	int maindone = FALSE;

	list = sess_list;
	while (list)
	{
		sess = list->data;

		if (!sess->gui->is_tab || !maindone)
		{
			if (sess->gui->is_tab)
				maindone = TRUE;
			if (id != -1)
				GTK_CHECK_MENU_ITEM (sess->gui->menu_item[id])->active = state;
			if (callback)
				callback (sess);
		}

		list = list->next;
	}
}
