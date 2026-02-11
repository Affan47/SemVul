complete_add_assertion (GkmTransaction *transaction, GObject *object, gpointer user_data)
{
	GkmAssertion *assertion = GKM_ASSERTION (user_data);
	GkmXdgTrust *self = GKM_XDG_TRUST (object);

	if (gkm_transaction_get_failed (transaction))
		remove_assertion_from_trust (self, assertion, NULL);

	g_object_unref (assertion);
	return TRUE;
}
