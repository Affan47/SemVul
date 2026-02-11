set_cardparameter(struct cm4000_dev *dev)
{
	int i;
	unsigned int iobase = dev->p_dev->resource[0]->start;
	u_int8_t stopbits = 0x02;

	DEBUGP(3, dev, "-> set_cardparameter\n");

	dev->flags1 = dev->flags1 | (((dev->baudv - 1) & 0x0100) >> 8);
	xoutb(dev->flags1, REG_FLAGS1(iobase));
	DEBUGP(5, dev, "flags1 = 0x%02x\n", dev->flags1);


	xoutb((unsigned char)((dev->baudv - 1) & 0xFF), REG_BAUDRATE(iobase));

	DEBUGP(5, dev, "baudv = %i -> write 0x%02x\n", dev->baudv,
	      ((dev->baudv - 1) & 0xFF));


	for (i = 0; i < ARRAY_SIZE(card_fixups); i++) {
		if (!memcmp(dev->atr, card_fixups[i].atr,
			    card_fixups[i].atr_len))
			stopbits = card_fixups[i].stopbits;
	}
	xoutb(stopbits, REG_STOPBITS(iobase));

	DEBUGP(3, dev, "<- set_cardparameter\n");
}
