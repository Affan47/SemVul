native_init_IRQ(void)
{
	int i;


	x86_init.irqs.pre_vector_init();

	apic_intr_init();


	i = FIRST_EXTERNAL_VECTOR;
#ifndef CONFIG_X86_LOCAL_APIC
#define first_system_vector NR_VECTORS
#endif
	for_each_clear_bit_from(i, used_vectors, first_system_vector) {

		set_intr_gate(i, irq_entries_start +
				8 * (i - FIRST_EXTERNAL_VECTOR));
	}
#ifdef CONFIG_X86_LOCAL_APIC
	for_each_clear_bit_from(i, used_vectors, NR_VECTORS)
		set_intr_gate(i, spurious_interrupt);
#endif

	if (!acpi_ioapic && !of_ioapic && nr_legacy_irqs())
		setup_irq(2, &irq2);

#ifdef CONFIG_X86_32
	irq_ctx_init(smp_processor_id());
#endif
}
