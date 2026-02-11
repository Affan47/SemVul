print_kretprobe_event(struct trace_iterator *iter, int flags,
		      struct trace_event *event)
{
	struct kretprobe_trace_entry_head *field;
	struct trace_seq *s = &iter->seq;
	struct trace_probe *tp;
	u8 *data;
	int i;

	field = (struct kretprobe_trace_entry_head *)iter->ent;
	tp = container_of(event, struct trace_probe, call.event);

	trace_seq_printf(s, "%s: (", trace_event_name(&tp->call));

	if (!seq_print_ip_sym(s, field->ret_ip, flags | TRACE_ITER_SYM_OFFSET))
		goto out;

	trace_seq_puts(s, " <- ");

	if (!seq_print_ip_sym(s, field->func, flags & ~TRACE_ITER_SYM_OFFSET))
		goto out;

	trace_seq_putc(s, ')');

	data = (u8 *)&field[1];
	for (i = 0; i < tp->nr_args; i++)
		if (!tp->args[i].type->print(s, tp->args[i].name,
					     data + tp->args[i].offset, field))
			goto out;

	trace_seq_putc(s, '\n');

 out:
	return trace_handle_return(s);
}
