tpci200_get_clockrate(struct ipack_device *dev)
{
	struct tpci200_board *tpci200 = check_slot(dev);
	__le16 __iomem *addr;

	if (!tpci200)
		return -ENODEV;

	addr = &tpci200->info->interface_regs->control[dev->slot];
	return (ioread16(addr) & TPCI200_CLK32) ? 32 : 8;
}
