sata_rcar_interrupt(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	struct sata_rcar_priv *priv = host->private_data;
	void __iomem *base = priv->base;
	unsigned int handled = 0;
	struct ata_port *ap;
	u32 sataintstat;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	sataintstat = ioread32(base + SATAINTSTAT_REG);
	sataintstat &= SATA_RCAR_INT_MASK;
	if (!sataintstat)
		goto done;

	iowrite32(~sataintstat & 0x7ff, base + SATAINTSTAT_REG);

	ap = host->ports[0];

	if (sataintstat & SATAINTSTAT_ATA)
		sata_rcar_ata_interrupt(ap);

	if (sataintstat & SATAINTSTAT_SERR)
		sata_rcar_serr_interrupt(ap);

	handled = 1;
done:
	spin_unlock_irqrestore(&host->lock, flags);

	return IRQ_RETVAL(handled);
}
