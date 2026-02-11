xen_free_irq(unsigned irq)
{
	struct irq_info *info = irq_get_handler_data(irq);

	if (WARN_ON(!info))
		return;

	list_del(&info->list);

	irq_set_handler_data(irq, NULL);

	WARN_ON(info->refcnt > 0);

	kfree(info);


	if (irq < nr_legacy_irqs())
		return;

	irq_free_desc(irq);
}
