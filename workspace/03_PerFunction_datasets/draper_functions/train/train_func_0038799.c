io2_isClosed(CTX ctx, kio_t *io2)
{
	return (io2->isRunning == 0 && io2->top >= io2->tail);
}
