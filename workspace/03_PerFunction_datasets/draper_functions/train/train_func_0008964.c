pacpi_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	int unit = adev->devno;
	struct pata_acpi *acpi = ap->private_data;
	const struct ata_timing *t;

	if (!(acpi->gtm.flags & 0x10))
		unit = 0;


	t = ata_timing_find_mode(adev->pio_mode);
	acpi->gtm.drive[unit].pio = t->cycle;
	ata_acpi_stm(ap, &acpi->gtm);

	ata_acpi_gtm(ap, &acpi->gtm);
}
