ahd_handle_lqiphase_error(struct ahd_softc *ahd, u_int lqistat1)
{


	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CLRLQIINT1, lqistat1);


	ahd_set_active_fifo(ahd);
	if ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0
	 && (ahd_inb(ahd, MDFFSTAT) & DLZERO) != 0) {
		if ((lqistat1 & LQIPHASE_LQ) != 0) {
			printk("LQIRETRY for LQIPHASE_LQ\n");
			ahd_outb(ahd, LQCTL2, LQIRETRY);
		} else if ((lqistat1 & LQIPHASE_NLQ) != 0) {
			printk("LQIRETRY for LQIPHASE_NLQ\n");
			ahd_outb(ahd, LQCTL2, LQIRETRY);
		} else
			panic("ahd_handle_lqiphase_error: No phase errors\n");
		ahd_dump_card_state(ahd);
		ahd_outb(ahd, CLRINT, CLRSCSIINT);
		ahd_unpause(ahd);
	} else {
		printk("Resetting Channel for LQI Phase error\n");
		ahd_dump_card_state(ahd);
		ahd_reset_channel(ahd, 'A', TRUE);
	}
}
