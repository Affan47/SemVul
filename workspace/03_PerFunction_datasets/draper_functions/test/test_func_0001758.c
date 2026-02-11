run_async_ready_callback (GcrGnupgProcess *self)
{
	GAsyncReadyCallback callback;
	gpointer user_data;

	_gcr_debug ("running async callback");


	callback = self->pv->async_callback;
	user_data = self->pv->user_data;
	self->pv->async_callback = NULL;
	self->pv->user_data = NULL;

	if (callback != NULL)
		(callback) (G_OBJECT (self), G_ASYNC_RESULT (self), user_data);
}
