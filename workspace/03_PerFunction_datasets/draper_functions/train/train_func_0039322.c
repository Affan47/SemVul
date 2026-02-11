ahd_read_flexport(struct ahd_softc *ahd, u_int addr, uint8_t *value)
{
	int	error;

	AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
	if (addr > 7)
		panic("ahd_read_flexport: address out of range");
	ahd_outb(ahd, BRDCTL, BRDRW|BRDEN|(addr << 3));
	error = ahd_wait_flexport(ahd);
	if (error != 0)
		return (error);
	*value = ahd_inb(ahd, BRDDAT);
	ahd_outb(ahd, BRDCTL, 0);
	ahd_flush_device_writes(ahd);
	return (0);
}
