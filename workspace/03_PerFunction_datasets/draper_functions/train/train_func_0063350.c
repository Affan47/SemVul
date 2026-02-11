pdc2027x_cable_detect(struct ata_port *ap)
{
	u32 cgcr;


	cgcr = ioread32(port_mmio(ap, PDC_GLOBAL_CTL));
	if (cgcr & (1 << 26))
		goto cbl40;

	PDPRINTK("No cable or 80-conductor cable on port %d\n", ap->port_no);

	return ATA_CBL_PATA80;
cbl40:
	printk(KERN_INFO DRV_NAME ": 40-conductor cable detected on port %d\n", ap->port_no);
	return ATA_CBL_PATA40;
}
