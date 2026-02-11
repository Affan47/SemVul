midgard_transaction_new (MidgardConnection *mgd)
{
	g_return_val_if_fail(mgd != NULL, NULL);

	MidgardTransaction *self = g_object_new (MIDGARD_TYPE_TRANSACTION, "connection", mgd, NULL);

	if (!self)
		return NULL;

	return self;
}
