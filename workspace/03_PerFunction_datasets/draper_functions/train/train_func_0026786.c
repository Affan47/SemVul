gck_session_set_interaction (GckSession *self,
                             GTlsInteraction *interaction)
{
	GTlsInteraction *previous;
	g_return_if_fail (GCK_IS_SESSION (self));
	g_return_if_fail (interaction == NULL || G_IS_TLS_INTERACTION (interaction));

	if (interaction)
		g_object_ref (interaction);

	g_mutex_lock (self->pv->mutex);

		previous = self->pv->interaction;
		self->pv->interaction = interaction;

	g_mutex_unlock (self->pv->mutex);

	if (previous)
		g_object_unref (previous);
}
