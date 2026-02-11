ata_sff_dma_pause(struct ata_port *ap)
{
	if (ap->ops->sff_check_altstatus || ap->ioaddr.altstatus_addr) {


		ata_sff_altstatus(ap);
		return;
	}


	BUG();
}
