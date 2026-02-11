smp_irq_move_cleanup_interrupt(void)
{
	unsigned vector, me;

	entering_ack_irq();


	raw_spin_lock(&vector_lock);

	me = smp_processor_id();
	for (vector = FIRST_EXTERNAL_VECTOR; vector < NR_VECTORS; vector++) {
		struct apic_chip_data *data;
		struct irq_desc *desc;
		unsigned int irr;

	retry:
		desc = __this_cpu_read(vector_irq[vector]);
		if (IS_ERR_OR_NULL(desc))
			continue;

		if (!raw_spin_trylock(&desc->lock)) {
			raw_spin_unlock(&vector_lock);
			cpu_relax();
			raw_spin_lock(&vector_lock);
			goto retry;
		}

		data = apic_chip_data(irq_desc_get_irq_data(desc));
		if (!data)
			goto unlock;


		if (data->move_in_progress ||
		    !cpumask_test_cpu(me, data->old_domain))
			goto unlock;


		if (vector == data->cfg.vector &&
		    cpumask_test_cpu(me, data->domain))
			goto unlock;

		irr = apic_read(APIC_IRR + (vector / 32 * 0x10));


		if (irr  & (1 << (vector % 32))) {
			apic->send_IPI_self(IRQ_MOVE_CLEANUP_VECTOR);
			goto unlock;
		}
		__this_cpu_write(vector_irq[vector], VECTOR_UNUSED);
		cpumask_clear_cpu(me, data->old_domain);
unlock:
		raw_spin_unlock(&desc->lock);
	}

	raw_spin_unlock(&vector_lock);

	exiting_irq();
}
