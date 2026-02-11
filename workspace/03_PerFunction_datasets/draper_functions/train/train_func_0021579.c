mptspi_write_width(struct scsi_target *starget, int width)
{
	struct _CONFIG_PAGE_SCSI_DEVICE_1 pg1;
	u32 nego;

	if (!width) {
		spi_dt(starget) = 0;
		if (spi_period(starget) < 10)
			spi_period(starget) = 10;
	}

	spi_width(starget) = width;

	nego = mptspi_getRP(starget);

	pg1.RequestedParameters = cpu_to_le32(nego);
	pg1.Reserved = 0;
	pg1.Configuration = 0;

	mptspi_write_spi_device_pg1(starget, &pg1);
}
