ep_is_in_ignored (EProxy *proxy,
                  const gchar *host)
{
	EProxyPrivate *priv;
	GSList * l;
	gchar *hn;

	g_return_val_if_fail (proxy != NULL, FALSE);
	g_return_val_if_fail (host != NULL, FALSE);

	priv = proxy->priv;
	if (!priv->ign_hosts)
		return FALSE;

	hn = g_ascii_strdown (host, -1);

	for (l = priv->ign_hosts; l; l = l->next) {
		if (*((gchar *) l->data) == '*') {
			if (g_str_has_suffix (hn, ((gchar *) l->data) + 1)) {
				g_free (hn);
				return TRUE;
			}
		} else if (strcmp (hn, l->data) == 0) {
				g_free (hn);
				return TRUE;
		}
	}
	g_free (hn);

	return FALSE;
}
