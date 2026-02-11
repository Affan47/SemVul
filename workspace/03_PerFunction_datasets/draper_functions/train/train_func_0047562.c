gda_capi_provider_xa_recover (GdaServerProvider *provider, GdaConnection *cnc,
				  G_GNUC_UNUSED GError **error)
{
	CapiConnectionData *cdata;

	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), NULL);
	g_return_val_if_fail (gda_connection_get_provider (cnc) == provider, NULL);

	cdata = (CapiConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return NULL;

	TO_IMPLEMENT;
	return NULL;
}
