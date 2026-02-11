tick_broadcast_set_affinity(struct clock_event_device *bc,
					const struct cpumask *cpumask)
{
	if (!(bc->features & CLOCK_EVT_FEAT_DYNIRQ))
		return;

	if (cpumask_equal(bc->cpumask, cpumask))
		return;

	bc->cpumask = cpumask;
	irq_set_affinity(bc->irq, bc->cpumask);
}
