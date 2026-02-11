irq_domain_alloc_irq_data(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *irq_data;
	struct irq_domain *parent;
	int i;


	for (i = 0; i < nr_irqs; i++) {
		irq_data = irq_get_irq_data(virq + i);
		irq_data->domain = domain;

		for (parent = domain->parent; parent; parent = parent->parent) {
			irq_data = irq_domain_insert_irq_data(parent, irq_data);
			if (!irq_data) {
				irq_domain_free_irq_data(virq, i + 1);
				return -ENOMEM;
			}
		}
	}

	return 0;
}
