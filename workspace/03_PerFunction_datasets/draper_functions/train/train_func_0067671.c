system_hostname_changed_cb (NMSettings *settings,
                            GParamSpec *pspec,
                            gpointer user_data)
{
	NMManager *self = NM_MANAGER (user_data);
	NMManagerPrivate *priv = NM_MANAGER_GET_PRIVATE (self);
	char *hostname;

	hostname = nm_settings_get_hostname (priv->settings);
	if (!hostname && !priv->hostname)
		return;
	if (hostname && priv->hostname && !strcmp (hostname, priv->hostname))
		return;

	g_free (priv->hostname);
	priv->hostname = (hostname && strlen (hostname)) ? g_strdup (hostname) : NULL;
	g_object_notify (G_OBJECT (self), NM_MANAGER_HOSTNAME);

	g_free (hostname);
}
