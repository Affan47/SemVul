profile_tick(int type)
{
	struct pt_regs *regs = get_irq_regs();

	if (!user_mode(regs) && prof_cpu_mask != NULL &&
	    cpumask_test_cpu(smp_processor_id(), prof_cpu_mask))
		profile_hit(type, (void *)profile_pc(regs));
}
