post(struct kmmio_probe *p, unsigned long condition,
							struct pt_regs *regs)
{
	struct trap_reason *my_reason = &get_cpu_var(pf_reason);
	struct mmiotrace_rw *my_trace = &get_cpu_var(cpu_trace);


	my_reason->active_traces--;
	if (my_reason->active_traces) {
		pr_emerg("unexpected post handler");
		BUG();
	}

	switch (my_reason->type) {
	case REG_READ:
		my_trace->value = get_ins_reg_val(my_reason->ip, regs);
		break;
	default:
		break;
	}

	mmio_trace_rw(my_trace);
	put_cpu_var(cpu_trace);
	put_cpu_var(pf_reason);
}
