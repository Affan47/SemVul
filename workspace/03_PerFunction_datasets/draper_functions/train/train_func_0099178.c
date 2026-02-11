_e2_filetype_dialog_response_cb (GtkDialog *dialog, gint response,
	E2_FileTypeDlg2Runtime *rt)
{
	printd (DEBUG, "response_cb (dialog:_,response:%d,rt:_)", response);
	gtk_widget_destroy (GTK_WIDGET (dialog));
	gchar *action;

	gchar *item = g_strconcat ("\"", rt->utfpath, "\"", NULL);

	switch (response)
	{
		case E2_RESPONSE_USER1:
		case E2_RESPONSE_USER2:
		case E2_RESPONSE_USER3:
		case 124:
			rt->processed = E2_TYPE_HANDLED;
			break;
		case GTK_RESPONSE_ACCEPT:
		case 125:
			rt->processed = E2_TYPE_NOTHANDLED;
			break;
		default:
			rt->processed = E2_TYPE_CANCELLED;
			break;
	}
	gtk_main_quit ();

	switch (response)
	{


		case GTK_RESPONSE_ACCEPT:

			e2_filetype_config_show (NULL);
			break;
		case E2_RESPONSE_USER1:
			action = g_strconcat (_A(5),".",_A(39), NULL);
			gdk_threads_leave ();
			e2_action_run_simple_from (action, item, NULL);
			gdk_threads_enter ();
			g_free (action);
			break;
		case E2_RESPONSE_USER2:
			action = g_strconcat (_A(5),".",_A(101), NULL);
			gdk_threads_leave ();
			e2_action_run_simple_from (action, item, NULL);
			gdk_threads_enter ();
			g_free (action);
			break;
		case E2_RESPONSE_USER3:
			action = g_strconcat (_A(5),".",_A(62), NULL);
			gdk_threads_leave ();
			e2_action_run_simple_from (action, item, NULL);
			gdk_threads_enter ();
			g_free (action);
			break;
		case 124:
#ifdef E2_COMMANDQ
			e2_command_run (item, E2_COMMAND_RANGE_DEFAULT, FALSE);
#else
			e2_command_run (item, E2_COMMAND_RANGE_DEFAULT);
#endif
			break;
		default:
			break;
	}
	gtk_widget_grab_focus (curr_view->treeview);
	g_free (item);
}
