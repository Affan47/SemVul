gkm_transaction_dispose (GObject *obj)
{
	GkmTransaction *self = GKM_TRANSACTION (obj);

	if (!self->completed)
		gkm_transaction_complete (self);

	G_OBJECT_CLASS (gkm_transaction_parent_class)->dispose (obj);
}
