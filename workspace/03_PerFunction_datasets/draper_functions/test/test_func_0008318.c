nm_setting_connection_add_permission (NMSettingConnection *setting,
                                      const char *ptype,
                                      const char *pitem,
                                      const char *detail)
{
	NMSettingConnectionPrivate *priv;
	Permission *p;
	GSList *iter;

	g_return_val_if_fail (NM_IS_SETTING_CONNECTION (setting), FALSE);
	g_return_val_if_fail (ptype, FALSE);
	g_return_val_if_fail (strlen (ptype) > 0, FALSE);
	g_return_val_if_fail (detail == NULL, FALSE);


	g_return_val_if_fail (strcmp (ptype, "user") == 0, FALSE);

	priv = NM_SETTING_CONNECTION_GET_PRIVATE (setting);


	for (iter = priv->permissions; iter; iter = g_slist_next (iter)) {
		p = iter->data;
		if (strcmp (pitem, p->item) == 0)
			return FALSE;
	}

	p = permission_new (pitem);
	g_return_val_if_fail (p != NULL, FALSE);
	priv->permissions = g_slist_append (priv->permissions, p);

	return TRUE;
}
