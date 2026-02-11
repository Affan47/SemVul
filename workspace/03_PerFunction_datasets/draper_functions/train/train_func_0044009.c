regmap_del_irq_chip(int irq, struct regmap_irq_chip_data *d)
{
	if (!d)
		return;

	free_irq(irq, d);
	irq_domain_remove(d->domain);
	kfree(d->wake_buf);
	kfree(d->mask_buf_def);
	kfree(d->mask_buf);
	kfree(d->status_reg_buf);
	kfree(d->status_buf);
	kfree(d);
}
