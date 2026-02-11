ce_page_ppp_new (NMConnection *connection,
                 GtkWindow *parent_window,
                 NMClient *client,
                 NMRemoteSettings *settings,
                 const char **out_secrets_setting_name,
                 GError **error)
{
	CEPagePpp *self;
	CEPagePppPrivate *priv;
	NMSettingConnection *s_con;

	self = CE_PAGE_PPP (ce_page_new (CE_TYPE_PAGE_PPP,
	                                 connection,
	                                 parent_window,
	                                 client,
	                                 settings,
	                                 UIDIR "/ce-page-ppp.ui",
	                                 "PppPage",
	                                 _("PPP Settings")));
	if (!self) {
		g_set_error_literal (error, NMA_ERROR, NMA_ERROR_GENERIC, _("Could not load PPP user interface."));
		return NULL;
	}

	ppp_private_init (self);
	priv = CE_PAGE_PPP_GET_PRIVATE (self);

	priv->setting = nm_connection_get_setting_ppp (connection);
	if (!priv->setting) {
		priv->setting = NM_SETTING_PPP (nm_setting_ppp_new ());
		nm_connection_add_setting (connection, NM_SETTING (priv->setting));
	}

	priv->window_group = gtk_window_group_new ();

	s_con = nm_connection_get_setting_connection (connection);
	g_assert (s_con);
	priv->connection_id = g_strdup (nm_setting_connection_get_id (s_con));

	g_signal_connect (self, "initialized", G_CALLBACK (finish_setup), NULL);

	*out_secrets_setting_name = NM_SETTING_PPP_SETTING_NAME;

	return CE_PAGE (self);
}
