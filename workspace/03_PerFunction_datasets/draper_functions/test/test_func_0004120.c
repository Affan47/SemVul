nsc_ircc_fir_interrupt(struct nsc_ircc_cb *self, int iobase,
				   int eir)
{
	__u8 bank;

	bank = inb(iobase+BSR);


	if (eir & EIR_SFIF_EV) {

		if (nsc_ircc_dma_receive_complete(self, iobase)) {

			self->ier = IER_SFIF_IE;
		} else {
			self->ier = IER_SFIF_IE | IER_TMR_IE;
		}
	} else if (eir & EIR_TMR_EV) {

		switch_bank(iobase, BANK4);
		outb(0, iobase+IRCR1);


		switch_bank(iobase, BANK0);
		outb(ASCR_CTE, iobase+ASCR);


		if (self->io.direction == IO_XMIT) {
			nsc_ircc_dma_xmit(self, iobase);


			self->ier = IER_DMA_IE;
		} else {

			if (nsc_ircc_dma_receive_complete(self, iobase)) {
				self->ier = IER_SFIF_IE;
			} else {
				self->ier = IER_SFIF_IE | IER_TMR_IE;
			}
		}
	} else if (eir & EIR_DMA_EV) {

		if (nsc_ircc_dma_xmit_complete(self)) {
			if(self->new_speed != 0) {


				self->ier = IER_TXEMP_IE;
			} else {


				if (irda_device_txqueue_empty(self->netdev)) {

					nsc_ircc_dma_receive(self);
					self->ier = IER_SFIF_IE;
				} else
					net_warn_ratelimited("%s(), potential Tx queue lockup !\n",
							     __func__);
			}
		} else {

			self->ier = IER_DMA_IE;
		}
	} else if (eir & EIR_TXEMP_EV) {


		self->ier = nsc_ircc_change_speed(self, self->new_speed);
		self->new_speed = 0;
		netif_wake_queue(self->netdev);

	}

	outb(bank, iobase+BSR);
}
