xen_setup_gdt(int cpu)
{
	if (xen_feature(XENFEAT_auto_translated_physmap)) {
#ifdef CONFIG_X86_64
		unsigned long dummy;

		load_percpu_segment(cpu);
		switch_to_new_gdt(cpu);


		asm volatile ("pushq %0\n"
			      "leaq 1f(%%rip),%0\n"
			      "pushq %0\n"
			      "lretq\n"
			      "1:\n"
			      : "=&r" (dummy) : "0" (__KERNEL_CS));


		loadsegment(es, 0);
		loadsegment(ds, 0);
		loadsegment(fs, 0);
#else

		BUG();
#endif
		return;
	}
	pv_cpu_ops.write_gdt_entry = xen_write_gdt_entry_boot;
	pv_cpu_ops.load_gdt = xen_load_gdt_boot;

	setup_stack_canary_segment(0);
	switch_to_new_gdt(0);

	pv_cpu_ops.write_gdt_entry = xen_write_gdt_entry;
	pv_cpu_ops.load_gdt = xen_load_gdt;
}
