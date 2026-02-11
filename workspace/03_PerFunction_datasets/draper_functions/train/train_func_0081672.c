ce_page_mobile_new (NMConnection *connection,
                    GtkWindow *parent_window,
                    NMClient *client,
                    NMRemoteSettings *settings,
                    const char **out_secrets_setting_name,
                    GError **error)
{
	CEPageMobile *self;
	CEPageMobilePrivate *priv;

	self = CE_PAGE_MOBILE (ce_page_new (CE_TYPE_PAGE_MOBILE,
	                                    connection,
	                                    parent_window,
	                                    client,
	                                    settings,
	                                    UIDIR "/ce-page-mobile.ui",
	                                    "MobilePage",
	                                    _("Mobile Broadband")));
	if (!self) {
		g_set_error_literal (error, NMA_ERROR, NMA_ERROR_GENERIC, _("Could not load mobile broadband user interface."));
		return NULL;
	}

	mobile_private_init (self);
	priv = CE_PAGE_MOBILE_GET_PRIVATE (self);

	priv->setting = nm_connection_get_setting (connection, NM_TYPE_SETTING_GSM);
	if (priv->setting)
		*out_secrets_setting_name = NM_SETTING_GSM_SETTING_NAME;
	else {
		priv->setting = nm_connection_get_setting (connection, NM_TYPE_SETTING_CDMA);
		if (priv->setting)
			*out_secrets_setting_name = NM_SETTING_CDMA_SETTING_NAME;
	}

	if (!priv->setting) {
		g_set_error (error, NMA_ERROR, NMA_ERROR_GENERIC, "%s", _("Unsupported mobile broadband connection type."));
		g_object_unref (self);
		return NULL;
	}

	g_signal_connect (self, "initialized", G_CALLBACK (finish_setup), NULL);

	return CE_PAGE (self);
}
