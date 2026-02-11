ata_eh_about_to_do(struct ata_link *link, struct ata_device *dev,
			unsigned int action)
{
	struct ata_port *ap = link->ap;
	struct ata_eh_info *ehi = &link->eh_info;
	struct ata_eh_context *ehc = &link->eh_context;
	unsigned long flags;

	spin_lock_irqsave(ap->lock, flags);

	ata_eh_clear_action(link, dev, ehi, action);


	if (!(ehc->i.flags & ATA_EHI_QUIET) && link != ap->slave_link)
		ap->pflags |= ATA_PFLAG_RECOVERED;

	spin_unlock_irqrestore(ap->lock, flags);
}
