cyy_interrupt(int irq, void *dev_id)
{
	int status;
	struct cyclades_card *cinfo = dev_id;
	void __iomem *base_addr, *card_base_addr;
	unsigned int chip, too_many, had_work;
	int index;

	if (unlikely(cinfo == NULL)) {
#ifdef CY_DEBUG_INTERRUPTS
		printk(KERN_DEBUG "cyy_interrupt: spurious interrupt %d\n",
				irq);
#endif
		return IRQ_NONE;
	}

	card_base_addr = cinfo->base_addr;
	index = cinfo->bus_index;


	if (unlikely(card_base_addr == NULL))
		return IRQ_HANDLED;


	do {
		had_work = 0;
		for (chip = 0; chip < cinfo->num_chips; chip++) {
			base_addr = cinfo->base_addr +
					(cy_chip_offset[chip] << index);
			too_many = 0;
			while ((status = readb(base_addr +
						(CySVRR << index))) != 0x00) {
				had_work++;


				if (1000 < too_many++)
					break;
				spin_lock(&cinfo->card_lock);
				if (status & CySRReceive)
					cyy_chip_rx(cinfo, chip, base_addr);
				if (status & CySRTransmit)
					cyy_chip_tx(cinfo, chip, base_addr);
				if (status & CySRModem)
					cyy_chip_modem(cinfo, chip, base_addr);
				spin_unlock(&cinfo->card_lock);
			}
		}
	} while (had_work);


	spin_lock(&cinfo->card_lock);
	cy_writeb(card_base_addr + (Cy_ClrIntr << index), 0);

	spin_unlock(&cinfo->card_lock);
	return IRQ_HANDLED;
}
