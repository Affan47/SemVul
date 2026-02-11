ahc_intr_enable(struct ahc_softc *ahc, int enable)
{
	u_int hcntrl;

	hcntrl = ahc_inb(ahc, HCNTRL);
	hcntrl &= ~INTEN;
	ahc->pause &= ~INTEN;
	ahc->unpause &= ~INTEN;
	if (enable) {
		hcntrl |= INTEN;
		ahc->pause |= INTEN;
		ahc->unpause |= INTEN;
	}
	ahc_outb(ahc, HCNTRL, hcntrl);
}
