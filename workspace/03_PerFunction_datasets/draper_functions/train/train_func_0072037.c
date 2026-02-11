gda_capi_provider_open_connection (GdaServerProvider *provider, GdaConnection *cnc,
				   GdaQuarkList *params, G_GNUC_UNUSED GdaQuarkList *auth,
				   G_GNUC_UNUSED guint *task_id, GdaServerProviderAsyncCallback async_cb,
				   G_GNUC_UNUSED gpointer cb_data)
{
	g_return_val_if_fail (GDA_IS_CAPI_PROVIDER (provider), FALSE);
	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), FALSE);


	if (async_cb) {
		gda_connection_add_event_string (cnc, _("Provider does not support asynchronous connection open"));
                return FALSE;
	}


	const gchar *db_name;
	db_name = gda_quark_list_find (params, "DB_NAME");
	if (!db_name) {
		gda_connection_add_event_string (cnc,
						 _("The connection string must contain the DB_NAME values"));
		return FALSE;
	}


	TO_IMPLEMENT;


	CapiConnectionData *cdata;
	cdata = g_new0 (CapiConnectionData, 1);
	gda_connection_internal_set_provider_data (cnc, cdata, (GDestroyNotify) gda_capi_free_cnc_data);
	TO_IMPLEMENT;


	TO_IMPLEMENT;

	return TRUE;
}
