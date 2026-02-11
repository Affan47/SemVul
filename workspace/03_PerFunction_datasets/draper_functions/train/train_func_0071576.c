geoclue_master_client_set_requirements_async (GeoclueMasterClient           *client,
					      GeoclueAccuracyLevel           min_accuracy,
					      int                            min_time,
					      gboolean                       require_updates,
					      GeoclueResourceFlags           allowed_resources,
					      GeoclueSetRequirementsCallback callback,
					      gpointer                       userdata)
{
	GeoclueMasterClientPrivate *priv = GET_PRIVATE (client);
	GeoclueMasterClientAsyncData *data;

	data = g_new (GeoclueMasterClientAsyncData, 1);
	data->client = client;
	data->callback = G_CALLBACK (callback);
	data->userdata = userdata;

	org_freedesktop_Geoclue_MasterClient_set_requirements_async
			(priv->proxy,
			 min_accuracy,
			 min_time,
			 require_updates,
			 allowed_resources,
			 (org_freedesktop_Geoclue_MasterClient_set_requirements_reply)set_requirements_callback,
			 data);
}
