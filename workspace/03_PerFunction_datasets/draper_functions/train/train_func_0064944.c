nm_setting_connection_get_permission (NMSettingConnection *setting,
                                      guint32 idx,
                                      const char **out_ptype,
                                      const char **out_pitem,
                                      const char **out_detail)
{
	NMSettingConnectionPrivate *priv;
	Permission *p;

	g_return_val_if_fail (NM_IS_SETTING_CONNECTION (setting), FALSE);

	priv = NM_SETTING_CONNECTION_GET_PRIVATE (setting);

	g_return_val_if_fail (idx < g_slist_length (priv->permissions), FALSE);

	p = g_slist_nth_data (priv->permissions, idx);
	if (out_ptype)
		*out_ptype = "user";
	if (out_pitem)
		*out_pitem = p->item;
	if (out_detail)
		*out_detail = NULL;

	return TRUE;
}
