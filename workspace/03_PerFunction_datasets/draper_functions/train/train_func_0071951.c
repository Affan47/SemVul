write_brdctl(struct ahc_softc *ahc, uint8_t value)
{
	uint8_t brdctl;

	if ((ahc->chip & AHC_CHIPID_MASK) == AHC_AIC7895) {
		brdctl = BRDSTB;
	 	if (ahc->channel == 'B')
			brdctl |= BRDCS;
	} else if ((ahc->features & AHC_ULTRA2) != 0) {
		brdctl = 0;
	} else {
		brdctl = BRDSTB|BRDCS;
	}
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	brdctl |= value;
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	if ((ahc->features & AHC_ULTRA2) != 0)
		brdctl |= BRDSTB_ULTRA2;
	else
		brdctl &= ~BRDSTB;
	ahc_outb(ahc, BRDCTL, brdctl);
	ahc_flush_device_writes(ahc);
	if ((ahc->features & AHC_ULTRA2) != 0)
		brdctl = 0;
	else
		brdctl &= ~BRDCS;
	ahc_outb(ahc, BRDCTL, brdctl);
}
