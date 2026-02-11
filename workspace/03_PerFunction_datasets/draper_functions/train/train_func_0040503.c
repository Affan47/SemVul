irq_dispose_mapping(unsigned int virq)
{
	struct irq_data *irq_data = irq_get_irq_data(virq);
	struct irq_domain *domain;

	if (!virq || !irq_data)
		return;

	domain = irq_data->domain;
	if (WARN_ON(domain == NULL))
		return;

	irq_domain_disassociate(domain, virq);
	irq_free_desc(virq);
}
