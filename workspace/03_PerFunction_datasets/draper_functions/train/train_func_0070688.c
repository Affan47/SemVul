print_graph_return(struct ftrace_graph_ret *trace, struct trace_seq *s,
		   struct trace_entry *ent, struct trace_iterator *iter,
		   u32 flags)
{
	unsigned long long duration = trace->rettime - trace->calltime;
	struct fgraph_data *data = iter->private;
	struct trace_array *tr = iter->tr;
	pid_t pid = ent->pid;
	int cpu = iter->cpu;
	int func_match = 1;
	int i;

	if (check_irq_return(iter, flags, trace->depth))
		return TRACE_TYPE_HANDLED;

	if (data) {
		struct fgraph_cpu_data *cpu_data;
		int cpu = iter->cpu;

		cpu_data = per_cpu_ptr(data->cpu_data, cpu);


		cpu_data->depth = trace->depth - 1;

		if (trace->depth < FTRACE_RETFUNC_DEPTH &&
		    !WARN_ON_ONCE(trace->depth < 0)) {
			if (cpu_data->enter_funcs[trace->depth] != trace->func)
				func_match = 0;
			cpu_data->enter_funcs[trace->depth] = 0;
		}
	}

	print_graph_prologue(iter, s, 0, 0, flags);


	print_graph_duration(tr, duration, s, flags);


	for (i = 0; i < trace->depth * TRACE_GRAPH_INDENT; i++)
		trace_seq_putc(s, ' ');


	if (func_match && !(flags & TRACE_GRAPH_PRINT_TAIL))
		trace_seq_puts(s, "}\n");
	else
		trace_seq_printf(s, "} /* %ps */\n", (void *)trace->func);


	if (flags & TRACE_GRAPH_PRINT_OVERRUN)
		trace_seq_printf(s, " (Overruns: %lu)\n",
				 trace->overrun);

	print_graph_irq(iter, trace->func, TRACE_GRAPH_RET,
			cpu, pid, flags);

	return trace_handle_return(s);
}
