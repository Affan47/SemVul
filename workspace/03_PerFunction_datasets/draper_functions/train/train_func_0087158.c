chameleon_parse_gdd(struct mcb_bus *bus,
			phys_addr_t mapbase,
			void __iomem *base)
{
	struct chameleon_gdd __iomem *gdd =
		(struct chameleon_gdd __iomem *) base;
	struct mcb_device *mdev;
	u32 offset;
	u32 size;
	int ret;
	__le32 reg1;
	__le32 reg2;

	mdev = mcb_alloc_dev(bus);
	if (!mdev)
		return -ENOMEM;

	reg1 = readl(&gdd->reg1);
	reg2 = readl(&gdd->reg2);
	offset = readl(&gdd->offset);
	size = readl(&gdd->size);

	mdev->id = GDD_DEV(reg1);
	mdev->rev = GDD_REV(reg1);
	mdev->var = GDD_VAR(reg1);
	mdev->bar = GDD_BAR(reg2);
	mdev->group = GDD_GRP(reg2);
	mdev->inst = GDD_INS(reg2);

	pr_debug("Found a 16z%03d\n", mdev->id);

	mdev->irq.start = GDD_IRQ(reg1);
	mdev->irq.end = GDD_IRQ(reg1);
	mdev->irq.flags = IORESOURCE_IRQ;

	mdev->mem.start = mapbase + offset;
	mdev->mem.end = mdev->mem.start + size - 1;
	mdev->mem.flags = IORESOURCE_MEM;

	mdev->is_added = false;

	ret = mcb_device_register(bus, mdev);
	if (ret < 0)
		goto err;

	return 0;

err:
	mcb_free_dev(mdev);

	return ret;
}
