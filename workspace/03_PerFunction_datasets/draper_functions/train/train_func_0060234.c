complete_run_process (GcrGnupgProcess *self)
{
	g_return_if_fail (self->pv->running);
	g_return_if_fail (!self->pv->complete);

	self->pv->running = FALSE;
	self->pv->complete = TRUE;

	if (self->pv->error == NULL) {
		_gcr_debug ("completed process");
	} else {
		_gcr_debug ("completed process with error: %s",
		            self->pv->error->message);
	}
}
