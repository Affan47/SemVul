check_in_enumerator_state (GckEnumeratorState *state)
{
	GckEnumeratorState *chained = NULL;
	GckEnumerator *self;

	g_assert (GCK_IS_ENUMERATOR (state->enumerator));
	self = state->enumerator;

	g_mutex_lock (self->pv->mutex);

		state->enumerator = NULL;
		g_assert (self->pv->the_state == NULL);
		self->pv->the_state = state;
		chained = state->chained;
		state->chained = NULL;

	g_mutex_unlock (self->pv->mutex);


	g_object_unref (self);

	if (chained)
		check_in_enumerator_state (chained);
}
