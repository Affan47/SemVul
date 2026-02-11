ahc_rem_scb_from_disc_list(struct ahc_softc *ahc, u_int prev, u_int scbptr)
{
	u_int next;

	ahc_outb(ahc, SCBPTR, scbptr);
	next = ahc_inb(ahc, SCB_NEXT);

	ahc_outb(ahc, SCB_CONTROL, 0);

	ahc_add_curscb_to_free_list(ahc);

	if (prev != SCB_LIST_NULL) {
		ahc_outb(ahc, SCBPTR, prev);
		ahc_outb(ahc, SCB_NEXT, next);
	} else
		ahc_outb(ahc, DISCONNECTED_SCBH, next);

	return (next);
}
