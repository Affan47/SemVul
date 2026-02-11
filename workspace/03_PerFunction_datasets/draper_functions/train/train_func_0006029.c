rspi_request_irq(struct device *dev, unsigned int irq,
			    irq_handler_t handler, const char *suffix,
			    void *dev_id)
{
	const char *name = devm_kasprintf(dev, GFP_KERNEL, "%s:%s",
					  dev_name(dev), suffix);
	if (!name)
		return -ENOMEM;

	return devm_request_irq(dev, irq, handler, 0, name, dev_id);
}
