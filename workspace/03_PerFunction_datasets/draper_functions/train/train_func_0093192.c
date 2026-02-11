via_ircc_is_receiving(struct via_ircc_cb *self)
{
	int status = FALSE;
	int iobase;

	IRDA_ASSERT(self != NULL, return FALSE;);

	iobase = self->io.fir_base;
	if (CkRxRecv(iobase, self))
		status = TRUE;

	pr_debug("%s(): status=%x....\n", __func__, status);

	return status;
}
