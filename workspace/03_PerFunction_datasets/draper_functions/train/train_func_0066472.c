irq_create_strict_mappings(struct irq_domain *domain, unsigned int irq_base,
			       irq_hw_number_t hwirq_base, int count)
{
	struct device_node *of_node;
	int ret;

	of_node = irq_domain_get_of_node(domain);
	ret = irq_alloc_descs(irq_base, irq_base, count,
			      of_node_to_nid(of_node));
	if (unlikely(ret < 0))
		return ret;

	irq_domain_associate_many(domain, irq_base, hwirq_base, count);
	return 0;
}
