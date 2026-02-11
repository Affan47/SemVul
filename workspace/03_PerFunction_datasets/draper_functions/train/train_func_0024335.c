sysrq_handle_showallcpus(int key)
{


	if (!trigger_all_cpu_backtrace()) {
		struct pt_regs *regs = NULL;

		if (in_irq())
			regs = get_irq_regs();
		if (regs) {
			pr_info("CPU%d:\n", smp_processor_id());
			show_regs(regs);
		}
		schedule_work(&sysrq_showallcpus);
	}
}
