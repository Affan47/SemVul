update_can_close (GeditWindow *window)
{
	GeditWindowPrivate *priv = window->priv;
	GList *tabs;
	GList *l;
	gboolean can_close = TRUE;

	gedit_debug (DEBUG_WINDOW);

	tabs = gedit_multi_notebook_get_all_tabs (priv->multi_notebook);

	for (l = tabs; l != NULL; l = g_list_next (l))
	{
		GeditTab *tab = l->data;

		if (!_gedit_tab_get_can_close (tab))
		{
			can_close = FALSE;
			break;
		}
	}

	if (can_close && (priv->inhibition_cookie != 0))
	{
		gtk_application_uninhibit (GTK_APPLICATION (g_application_get_default ()),
					   priv->inhibition_cookie);
		priv->inhibition_cookie = 0;
	}
	else if (!can_close && (priv->inhibition_cookie == 0))
	{
		priv->inhibition_cookie = gtk_application_inhibit (GTK_APPLICATION (g_application_get_default ()),
		                                                   GTK_WINDOW (window),
		                                                   GTK_APPLICATION_INHIBIT_LOGOUT,
		                                                   _("There are unsaved documents"));
	}

	g_list_free (tabs);
}
