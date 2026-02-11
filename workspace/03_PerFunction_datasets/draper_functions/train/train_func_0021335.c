sccnxp_handle_events(struct sccnxp_port *s)
{
	int i;
	u8 isr;

	do {
		isr = sccnxp_read(&s->port[0], SCCNXP_ISR_REG);
		isr &= s->imr;
		if (!isr)
			break;

		for (i = 0; i < s->uart.nr; i++) {
			if (s->opened[i] && (isr & ISR_RXRDY(i)))
				sccnxp_handle_rx(&s->port[i]);
			if (s->opened[i] && (isr & ISR_TXRDY(i)))
				sccnxp_handle_tx(&s->port[i]);
		}
	} while (1);
}
