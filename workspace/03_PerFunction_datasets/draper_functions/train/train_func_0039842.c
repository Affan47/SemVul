probe_irq_off(unsigned long val)
{
	int i, irq_found = 0, nr_of_irqs = 0;
	struct irq_desc *desc;

	for_each_irq_desc(i, desc) {
		raw_spin_lock_irq(&desc->lock);

		if (desc->istate & IRQS_AUTODETECT) {
			if (!(desc->istate & IRQS_WAITING)) {
				if (!nr_of_irqs)
					irq_found = i;
				nr_of_irqs++;
			}
			desc->istate &= ~IRQS_AUTODETECT;
			irq_shutdown(desc);
		}
		raw_spin_unlock_irq(&desc->lock);
	}
	mutex_unlock(&probing_active);

	if (nr_of_irqs > 1)
		irq_found = -irq_found;

	return irq_found;
}
