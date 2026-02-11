e_cal_backend_http_get_object (ECalBackendSync *backend,
                               EDataCal *cal,
                               GCancellable *cancellable,
                               const gchar *uid,
                               const gchar *rid,
                               gchar **object,
                               GError **error)
{
	ECalBackendHttp *cbhttp;
	ECalBackendHttpPrivate *priv;
	ECalComponent *comp = NULL;

	cbhttp = E_CAL_BACKEND_HTTP (backend);
	priv = cbhttp->priv;

	if (!priv->store) {
		g_propagate_error (error, EDC_ERROR (ObjectNotFound));
		return;
	}

	if (rid && *rid) {
		comp = e_cal_backend_store_get_component (priv->store, uid, rid);
		if (!comp) {
			g_propagate_error (error, EDC_ERROR (ObjectNotFound));
			return;
		}

		*object = e_cal_component_get_as_string (comp);
		g_object_unref (comp);
	} else {
		*object = e_cal_backend_store_get_components_by_uid_as_ical_string (priv->store, uid);
		if (!*object)
			g_propagate_error (error, EDC_ERROR (ObjectNotFound));
	}
}
