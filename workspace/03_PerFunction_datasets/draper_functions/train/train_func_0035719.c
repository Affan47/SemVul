gda_transaction_status_new (const gchar *name)
{
	GdaTransactionStatus *tstatus;

	tstatus = g_object_new (GDA_TYPE_TRANSACTION_STATUS, NULL);
	if (name)
		tstatus->name = g_strdup (name);

	return tstatus;
}
