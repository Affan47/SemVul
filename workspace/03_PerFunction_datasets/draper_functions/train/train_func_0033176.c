signer_toggled (GtkWidget *widget, CryptUIKeyChooser *chooser)
{
	const gchar *signer;

	g_assert (chooser->priv->signercheck);

	if (chooser->priv->settings) {
		signer = g_object_get_data ((GObject*) (chooser->priv->signercheck), "key");
		g_settings_set_string (chooser->priv->settings, "last-signer",
		                       signer ? signer : "");
	}

	g_signal_emit (chooser, signals[CHANGED], 0);
}
