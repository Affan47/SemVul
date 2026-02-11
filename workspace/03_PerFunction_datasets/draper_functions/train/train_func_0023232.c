apic_set_affinity(struct irq_data *irq_data,
			     const struct cpumask *dest, bool force)
{
	struct apic_chip_data *data = irq_data->chip_data;
	int err, irq = irq_data->irq;

	if (!config_enabled(CONFIG_SMP))
		return -EPERM;

	if (!cpumask_intersects(dest, cpu_online_mask))
		return -EINVAL;

	err = assign_irq_vector(irq, data, dest);
	return err ? err : IRQ_SET_MASK_OK;
}
