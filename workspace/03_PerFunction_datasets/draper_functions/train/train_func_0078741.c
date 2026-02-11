vt6420_prereset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ata_eh_context *ehc = &ap->link.eh_context;
	unsigned long timeout = jiffies + (HZ * 5);
	u32 sstatus, scontrol;
	int online;


	if (!(ap->pflags & ATA_PFLAG_LOADING))
		goto skip_scr;


	svia_scr_write(link, SCR_CONTROL, 0x300);
	svia_scr_read(link, SCR_CONTROL, &scontrol);


	do {
		ata_msleep(link->ap, 200);
		svia_scr_read(link, SCR_STATUS, &sstatus);
		if ((sstatus & 0xf) != 1)
			break;
	} while (time_before(jiffies, timeout));


	svia_scr_read(link, SCR_STATUS, &sstatus);
	svia_scr_read(link, SCR_CONTROL, &scontrol);

	online = (sstatus & 0xf) == 0x3;

	ata_port_info(ap,
		      "SATA link %s 1.5 Gbps (SStatus %X SControl %X)\n",
		      online ? "up" : "down", sstatus, scontrol);


	svia_scr_read(link, SCR_STATUS, &sstatus);

	if (!online) {

		ehc->i.action &= ~ATA_EH_RESET;
		return 0;
	}

 skip_scr:

	ata_sff_wait_ready(link, deadline);

	return 0;
}
