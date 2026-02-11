gda_connection_get_authentication (GdaConnection *cnc)
{
	const gchar *str;
	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), NULL);

	str = (const gchar *) cnc->priv->auth_string;
	if (!str)
		str = "";
	return str;
}
