ata_sff_port_init(struct ata_port *ap)
{
	INIT_DELAYED_WORK(&ap->sff_pio_task, ata_sff_pio_task);
	ap->ctl = ATA_DEVCTL_OBS;
	ap->last_ctl = 0xFF;
}
