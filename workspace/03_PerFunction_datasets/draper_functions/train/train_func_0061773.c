pdc_reset_port(struct ata_port *ap)
{
	void __iomem *ata_ctlstat_mmio = ap->ioaddr.cmd_addr + PDC_CTLSTAT;
	unsigned int i;
	u32 tmp;

	if (ap->flags & PDC_FLAG_GEN_II)
		pdc_not_at_command_packet_phase(ap);

	tmp = readl(ata_ctlstat_mmio);
	tmp |= PDC_RESET;
	writel(tmp, ata_ctlstat_mmio);

	for (i = 11; i > 0; i--) {
		tmp = readl(ata_ctlstat_mmio);
		if (tmp & PDC_RESET)
			break;

		udelay(100);

		tmp |= PDC_RESET;
		writel(tmp, ata_ctlstat_mmio);
	}

	tmp &= ~PDC_RESET;
	writel(tmp, ata_ctlstat_mmio);
	readl(ata_ctlstat_mmio);

	if (sata_scr_valid(&ap->link) && (ap->flags & PDC_FLAG_GEN_II)) {
		pdc_fpdma_reset(ap);
		pdc_clear_internal_debug_record_error_register(ap);
	}
}
