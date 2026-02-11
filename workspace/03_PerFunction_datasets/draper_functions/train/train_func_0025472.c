net2272_probe_init(struct device *dev, unsigned int irq)
{
	struct net2272 *ret;

	if (!irq) {
		dev_dbg(dev, "No IRQ!\n");
		return ERR_PTR(-ENODEV);
	}


	ret = kzalloc(sizeof(*ret), GFP_KERNEL);
	if (!ret)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&ret->lock);
	ret->irq = irq;
	ret->dev = dev;
	ret->gadget.ops = &net2272_ops;
	ret->gadget.max_speed = USB_SPEED_HIGH;


	ret->gadget.name = driver_name;

	return ret;
}
