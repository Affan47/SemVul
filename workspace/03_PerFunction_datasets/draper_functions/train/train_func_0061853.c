e_cal_backend_contacts_get_object_list (ECalBackendSync *backend,
                                        EDataCal *cal,
                                        GCancellable *cancellable,
                                        const gchar *sexp_string,
                                        GSList **objects,
                                        GError **perror)
{
	ECalBackendContacts *cbc = E_CAL_BACKEND_CONTACTS (backend);
	ECalBackendContactsPrivate *priv = cbc->priv;
	ECalBackendSExp *sexp = e_cal_backend_sexp_new (sexp_string);
	ContactRecordCB *cb_data;

	if (!sexp) {
		g_propagate_error (perror, EDC_ERROR (InvalidQuery));
		return;
	}

	cb_data = contact_record_cb_new (cbc, sexp, TRUE);

	g_rec_mutex_lock (&priv->tracked_contacts_lock);
	g_hash_table_foreach (priv->tracked_contacts, contact_record_cb, cb_data);
	g_rec_mutex_unlock (&priv->tracked_contacts_lock);

	*objects = cb_data->result;

	contact_record_cb_free (cb_data, FALSE);
}
