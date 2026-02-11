cleanup_crypto (GkmSession *self)
{
	g_assert (self->pv->current_operation == cleanup_crypto);

	if (self->pv->crypto_state && self->pv->crypto_destroy)
		(self->pv->crypto_destroy) (self->pv->crypto_state);
	self->pv->crypto_state = NULL;
	self->pv->crypto_destroy = NULL;
	self->pv->crypto_mechanism = 0;
	self->pv->crypto_method = 0;

	g_assert (GKM_IS_OBJECT (self->pv->current_object));
	if (self->pv->current_object)
		g_object_unref (self->pv->current_object);
	self->pv->current_object = NULL;

	if (self->pv->credential) {
		g_object_set_data (G_OBJECT (self->pv->credential), "owned-by-session", NULL);
		g_object_unref (self->pv->credential);
		self->pv->credential = NULL;
	}

	self->pv->current_operation = NULL;
}
