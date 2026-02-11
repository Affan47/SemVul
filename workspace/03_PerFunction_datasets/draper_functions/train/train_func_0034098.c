ata_eh_unload(struct ata_port *ap)
{
	struct ata_link *link;
	struct ata_device *dev;
	unsigned long flags;


	ata_for_each_link(link, ap, PMP_FIRST) {
		sata_scr_write(link, SCR_CONTROL, link->saved_scontrol & 0xff0);
		ata_for_each_dev(dev, link, ALL)
			ata_dev_disable(dev);
	}


	spin_lock_irqsave(ap->lock, flags);

	ata_port_freeze(ap);
	ap->pflags &= ~ATA_PFLAG_EH_PENDING;
	ap->pflags |= ATA_PFLAG_UNLOADED;

	spin_unlock_irqrestore(ap->lock, flags);
}
