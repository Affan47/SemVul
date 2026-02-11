gc_iface_master_client_position_start (GcMasterClient *client,
                                       GError         **error)
{
	GcMasterClientPrivate *priv = GET_PRIVATE (client);

	if (priv->position_providers) {
		if (error) {
			*error = g_error_new (GEOCLUE_ERROR,
			                      GEOCLUE_ERROR_FAILED,
			                      "Position interface already started");
		}
		return FALSE;
	}

	priv->position_started = TRUE;

	gc_master_client_init_position_providers (client);

	return TRUE;
}
