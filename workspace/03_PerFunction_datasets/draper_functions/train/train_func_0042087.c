function_trace_call(unsigned long ip, unsigned long parent_ip,
		    struct ftrace_ops *op, struct pt_regs *pt_regs)
{
	struct trace_array *tr = op->private;
	struct trace_array_cpu *data;
	unsigned long flags;
	int bit;
	int cpu;
	int pc;

	if (unlikely(!tr->function_enabled))
		return;

	pc = preempt_count();
	preempt_disable_notrace();

	bit = trace_test_and_set_recursion(TRACE_FTRACE_START, TRACE_FTRACE_MAX);
	if (bit < 0)
		goto out;

	cpu = smp_processor_id();
	data = per_cpu_ptr(tr->trace_buffer.data, cpu);
	if (!atomic_read(&data->disabled)) {
		local_save_flags(flags);
		trace_function(tr, ip, parent_ip, flags, pc);
	}
	trace_clear_recursion(bit);

 out:
	preempt_enable_notrace();
}
