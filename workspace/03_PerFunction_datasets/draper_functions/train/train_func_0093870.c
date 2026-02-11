ata_wait_register(struct ata_port *ap, void __iomem *reg, u32 mask, u32 val,
		      unsigned long interval, unsigned long timeout)
{
	unsigned long deadline;
	u32 tmp;

	tmp = ioread32(reg);


	deadline = ata_deadline(jiffies, timeout);

	while ((tmp & mask) == val && time_before(jiffies, deadline)) {
		ata_msleep(ap, interval);
		tmp = ioread32(reg);
	}

	return tmp;
}
