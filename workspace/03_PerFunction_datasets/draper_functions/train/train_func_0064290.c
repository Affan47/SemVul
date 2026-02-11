key_handle_key_press (GtkWidget *wid, GdkEventKey *evt, session *sess)
{
	struct key_binding *kb, *last = NULL;
	int keyval = evt->keyval;
	int mod, n;
	GSList *list;


	list = sess_list;
	while (list)
	{
		sess = list->data;
		if (sess->gui->input_box == wid)
		{
			if (sess->gui->is_tab)
				sess = current_tab;
			break;
		}
		list = list->next;
	}
	if (!list)
		return FALSE;
	current_sess = sess;

	if (plugin_emit_keypress (sess, evt->state, evt->keyval, evt->length, evt->string))
		return 1;


	if (!is_session (sess))
		return 1;

	mod = evt->state & (STATE_CTRL | STATE_ALT | STATE_SHIFT);

	kb = keys_root;
	while (kb)
	{
		if (kb->keyval == keyval && kb->mod == mod)
		{
			if (kb->action < 0 || kb->action > KEY_MAX_ACTIONS)
				return 0;


			if (last != NULL)
			{
				last->next = kb->next;
				kb->next = keys_root;
				keys_root = kb;
			}

			n = key_actions[kb->action].handler (wid, evt, kb->data1,
															 kb->data2, sess);
			switch (n)
			{
			case 0:
				return 1;
			case 2:
				g_signal_stop_emission_by_name (G_OBJECT (wid),
														"key_press_event");
				return 1;
			}
		}
		last = kb;
		kb = kb->next;
	}

	switch (keyval)
	{
	case GDK_space:
		key_action_tab_clean ();
		break;

#if defined(USE_GTKSPELL)

	case GDK_Return:
	case GDK_KP_Enter:
		if (!(evt->state & STATE_CTRL))
		{
			g_signal_stop_emission_by_name (G_OBJECT (wid), "key_press_event");
			mg_inputbox_cb (wid, sess->gui);
		}
#endif
	}

	return 0;
}
