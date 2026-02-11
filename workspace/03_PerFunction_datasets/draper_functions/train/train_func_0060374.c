auth_methods_button_clicked_cb (GtkWidget *button, gpointer user_data)
{
	CEPagePpp *self = CE_PAGE_PPP (user_data);
	CEPagePppPrivate *priv = CE_PAGE_PPP_GET_PRIVATE (self);
	GtkWidget *dialog, *toplevel;
	char *tmp;

	toplevel = gtk_widget_get_toplevel (CE_PAGE (self)->page);
	g_return_if_fail (gtk_widget_is_toplevel (toplevel));

	dialog = ppp_auth_methods_dialog_new (priv->refuse_eap,
	                                      priv->refuse_pap,
	                                      priv->refuse_chap,
	                                      priv->refuse_mschap,
	                                      priv->refuse_mschapv2);
	if (!dialog) {
		g_warning ("%s: failed to create the PPP authentication methods dialog!", __func__);
		return;
	}

	gtk_window_group_add_window (priv->window_group, GTK_WINDOW (dialog));
	if (!priv->window_added) {
		gtk_window_group_add_window (priv->window_group, GTK_WINDOW (toplevel));
		priv->window_added = TRUE;
	}

	gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (toplevel));
	tmp = g_strdup_printf (_("Editing PPP authentication methods for %s"), priv->connection_id);
	gtk_window_set_title (GTK_WINDOW (dialog), tmp);
	g_free (tmp);

	g_signal_connect (G_OBJECT (dialog), "response", G_CALLBACK (auth_methods_dialog_response_cb), self);

	gtk_widget_show_all (dialog);
}
