ahd_linux_show_info(struct seq_file *m, struct Scsi_Host *shost)
{
	struct	ahd_softc *ahd = *(struct ahd_softc **)shost->hostdata;
	char	ahd_info[256];
	u_int	max_targ;
	u_int	i;

	seq_printf(m, "Adaptec AIC79xx driver version: %s\n",
		  AIC79XX_DRIVER_VERSION);
	seq_printf(m, "%s\n", ahd->description);
	ahd_controller_info(ahd, ahd_info);
	seq_printf(m, "%s\n", ahd_info);
	seq_printf(m, "Allocated SCBs: %d, SG List Length: %d\n\n",
		  ahd->scb_data.numscbs, AHD_NSEG);

	max_targ = 16;

	if (ahd->seep_config == NULL)
		seq_puts(m, "No Serial EEPROM\n");
	else {
		seq_puts(m, "Serial EEPROM:\n");
		for (i = 0; i < sizeof(*ahd->seep_config)/2; i++) {
			if (((i % 8) == 0) && (i != 0)) {
				seq_putc(m, '\n');
			}
			seq_printf(m, "0x%.4x ",
				  ((uint16_t*)ahd->seep_config)[i]);
		}
		seq_putc(m, '\n');
	}
	seq_putc(m, '\n');

	if ((ahd->features & AHD_WIDE) == 0)
		max_targ = 8;

	for (i = 0; i < max_targ; i++) {

		ahd_dump_target_state(ahd, m, ahd->our_id, 'A',
				      i);
	}
	return 0;
}
