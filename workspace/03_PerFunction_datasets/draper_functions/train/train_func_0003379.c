pdc2027x_set_mode(struct ata_link *link, struct ata_device **r_failed)
{
	struct ata_port *ap = link->ap;
	struct ata_device *dev;
	int rc;

	rc = ata_do_set_mode(link, r_failed);
	if (rc < 0)
		return rc;

	ata_for_each_dev(dev, link, ENABLED) {
		pdc2027x_set_piomode(ap, dev);


		if (dev->xfer_shift == ATA_SHIFT_PIO) {
			u32 ctcr1 = ioread32(dev_mmio(ap, dev, PDC_CTCR1));
			ctcr1 |= (1 << 25);
			iowrite32(ctcr1, dev_mmio(ap, dev, PDC_CTCR1));

			PDPRINTK("Turn on prefetch\n");
		} else {
			pdc2027x_set_dmamode(ap, dev);
		}
	}
	return 0;
}
