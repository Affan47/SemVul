complete_set_modified (GkmTransaction *transaction,
                       GObject *obj,
                       gpointer user_data)
{
	GkmSecretObject *self = GKM_SECRET_OBJECT (obj);
	glong *old_modified = user_data;

	if (gkm_transaction_get_failed (transaction)) {
		self->pv->modified = *old_modified;

	} else {
		gkm_object_notify_attribute (GKM_OBJECT (obj), CKA_G_MODIFIED);
		g_object_notify (G_OBJECT (obj), "modified");
	}

	g_free (old_modified);
	return TRUE;
}
