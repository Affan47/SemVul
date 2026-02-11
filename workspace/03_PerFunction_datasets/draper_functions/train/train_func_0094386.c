create_vcnc (GdaDataPivot *pivot, GError **error)
{
	GdaConnection *vcnc;
	GError *lerror = NULL;
	if (pivot->priv->vcnc)
		return TRUE;

	g_mutex_lock (&provider_mutex);
	if (!virtual_provider)
		virtual_provider = gda_vprovider_data_model_new ();
	g_mutex_unlock (&provider_mutex);

	vcnc = gda_virtual_connection_open (virtual_provider, &lerror);
	if (! vcnc) {
		g_print ("Virtual ERROR: %s\n", lerror && lerror->message ? lerror->message : "No detail");
		if (lerror)
			g_error_free (lerror);
		g_set_error (error, GDA_DATA_PIVOT_ERROR, GDA_DATA_PIVOT_INTERNAL_ERROR,
			     "%s", _("Could not create virtual connection"));
		return FALSE;
	}

	pivot->priv->vcnc = vcnc;
	return TRUE;
}
