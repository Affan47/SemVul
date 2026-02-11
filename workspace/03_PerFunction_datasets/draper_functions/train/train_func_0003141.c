ahc_index_busy_tcl(struct ahc_softc *ahc, u_int tcl)
{
	u_int scbid;
	u_int target_offset;

	if ((ahc->flags & AHC_SCB_BTT) != 0) {
		u_int saved_scbptr;

		saved_scbptr = ahc_inb(ahc, SCBPTR);
		ahc_outb(ahc, SCBPTR, TCL_LUN(tcl));
		scbid = ahc_inb(ahc, SCB_64_BTT + TCL_TARGET_OFFSET(tcl));
		ahc_outb(ahc, SCBPTR, saved_scbptr);
	} else {
		target_offset = TCL_TARGET_OFFSET(tcl);
		scbid = ahc_inb(ahc, BUSY_TARGETS + target_offset);
	}

	return (scbid);
}
