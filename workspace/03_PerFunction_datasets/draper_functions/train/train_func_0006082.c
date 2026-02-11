smsc_ircc_sir_wait_hw_transmitter_finish(struct smsc_ircc_cb *self)
{
	int iobase = self->io.sir_base;
	int count = SMSC_IRCC2_HW_TRANSMITTER_TIMEOUT_US;


	while (count-- > 0 && !(inb(iobase + UART_LSR) & UART_LSR_TEMT))
		udelay(1);

	if (count < 0)
		pr_debug("%s(): stuck transmitter\n", __func__);
}
