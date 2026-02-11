dma_queue_emit_debugger_ready (DmaDebuggerQueue *self)
{
	gboolean busy;

	if (g_queue_is_empty(self->queue) && (self->last == NULL))
	{
		busy = FALSE;
	}
	else
	{
		busy = TRUE;
	}

	if (busy != self->busy)
	{

		self->busy = busy;
	}
}
