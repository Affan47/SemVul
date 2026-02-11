ahd_pci_test_register_access(struct ahd_softc *ahd)
{
	uint32_t cmd;
	u_int	 targpcistat;
	u_int	 pci_status1;
	int	 error;
	uint8_t	 hcntrl;

	error = EIO;


	cmd = ahd_pci_read_config(ahd->dev_softc, PCIR_COMMAND, 2);
	ahd_pci_write_config(ahd->dev_softc, PCIR_COMMAND,
			     cmd & ~PCIM_CMD_SERRESPEN, 2);


	hcntrl = ahd_inb(ahd, HCNTRL);
	if (hcntrl == 0xFF)
		goto fail;


	hcntrl &= ~CHIPRST;
	ahd_outb(ahd, HCNTRL, hcntrl|PAUSE);
	while (ahd_is_paused(ahd) == 0)
		;


	ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
	targpcistat = ahd_inb(ahd, TARGPCISTAT);
	ahd_outb(ahd, TARGPCISTAT, targpcistat);
	pci_status1 = ahd_pci_read_config(ahd->dev_softc,
					  PCIR_STATUS + 1, 1);
	ahd_pci_write_config(ahd->dev_softc, PCIR_STATUS + 1,
			     pci_status1, 1);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd_outb(ahd, CLRINT, CLRPCIINT);

	ahd_outb(ahd, SEQCTL0, PERRORDIS);
	ahd_outl(ahd, SRAM_BASE, 0x5aa555aa);
	if (ahd_inl(ahd, SRAM_BASE) != 0x5aa555aa)
		goto fail;

	if ((ahd_inb(ahd, INTSTAT) & PCIINT) != 0) {
		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		targpcistat = ahd_inb(ahd, TARGPCISTAT);
		if ((targpcistat & STA) != 0)
			goto fail;
	}

	error = 0;

fail:
	if ((ahd_inb(ahd, INTSTAT) & PCIINT) != 0) {

		ahd_set_modes(ahd, AHD_MODE_CFG, AHD_MODE_CFG);
		targpcistat = ahd_inb(ahd, TARGPCISTAT);


		ahd_outb(ahd, TARGPCISTAT, targpcistat);
		pci_status1 = ahd_pci_read_config(ahd->dev_softc,
						  PCIR_STATUS + 1, 1);
		ahd_pci_write_config(ahd->dev_softc, PCIR_STATUS + 1,
				     pci_status1, 1);
		ahd_outb(ahd, CLRINT, CLRPCIINT);
	}
	ahd_outb(ahd, SEQCTL0, PERRORDIS|FAILDIS);
	ahd_pci_write_config(ahd->dev_softc, PCIR_COMMAND, cmd, 2);
	return (error);
}
