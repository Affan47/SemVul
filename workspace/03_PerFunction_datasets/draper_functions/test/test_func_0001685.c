ahc_inb(struct ahc_softc * ahc, long port)
{
	uint8_t x;

	if (ahc->tag == BUS_SPACE_MEMIO) {
		x = readb(ahc->bsh.maddr + port);
	} else {
		x = inb(ahc->bsh.ioport + port);
	}
	mb();
	return (x);
}
