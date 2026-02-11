ahci_init_sw_activity(struct ata_link *link)
{
	struct ata_port *ap = link->ap;
	struct ahci_port_priv *pp = ap->private_data;
	struct ahci_em_priv *emp = &pp->em_priv[link->pmp];


	emp->saved_activity = emp->activity = 0;
	setup_timer(&emp->timer, ahci_sw_activity_blink, (unsigned long)link);


	if (emp->blink_policy)
		link->flags |= ATA_LFLAG_SW_ACTIVITY;
}
