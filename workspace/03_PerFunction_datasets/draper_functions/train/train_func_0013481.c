test_set_transacted_fail_revert (void)
{
	GkmTransaction *transaction = gkm_transaction_new ();
	GkmSecretData *data = g_object_new (GKM_TYPE_SECRET_DATA, NULL);
	GkmSecret *old = gkm_secret_new_from_password ("old");
	GkmSecret *secret = gkm_secret_new_from_password ("secret");


	gkm_secret_data_set_secret (data, "my-identifier", old);
	g_assert (gkm_secret_data_get_secret (data, "my-identifier") == old);


	gkm_secret_data_set_transacted (data, transaction, "my-identifier", secret);
	g_assert (!gkm_transaction_get_failed (transaction));
	g_assert (gkm_secret_data_get_secret (data, "my-identifier") == secret);


	gkm_transaction_fail (transaction, CKR_CANCEL);
	gkm_transaction_complete (transaction);
	g_assert (gkm_transaction_get_failed (transaction));
	g_assert (gkm_secret_data_get_secret (data, "my-identifier") == old);

	g_object_unref (old);
	g_object_unref (data);
	g_object_unref (secret);
	g_object_unref (transaction);
}
