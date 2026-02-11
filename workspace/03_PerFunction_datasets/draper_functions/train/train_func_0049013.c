ali_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct ata_device *pair = ata_dev_pair(adev);
	struct ata_timing t;
	unsigned long T =  1000000000 / 33333;

	ata_timing_compute(adev, adev->pio_mode, &t, T, 1);
	if (pair) {
		struct ata_timing p;
		ata_timing_compute(pair, pair->pio_mode, &p, T, 1);
		ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
		if (pair->dma_mode) {
			ata_timing_compute(pair, pair->dma_mode, &p, T, 1);
			ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
		}
	}


	if (adev->class != ATA_DEV_ATA)
		ali_fifo_control(ap, adev, 0x00);
	ali_program_modes(ap, adev, &t, 0);
	if (adev->class == ATA_DEV_ATA)
		ali_fifo_control(ap, adev, 0x05);

}
