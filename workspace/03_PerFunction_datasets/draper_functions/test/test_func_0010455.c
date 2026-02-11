complete_set_secret (GkmTransaction *transaction, GObject *obj, gpointer user_data)
{
	if (!gkm_transaction_get_failed (transaction)) {
		gkm_object_notify_attribute (GKM_OBJECT (obj), CKA_VALUE);
	}

	return TRUE;
}
