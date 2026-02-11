kretprobe_event_define_fields(struct trace_event_call *event_call)
{
	int ret, i;
	struct kretprobe_trace_entry_head field;
	struct trace_kprobe *tk = (struct trace_kprobe *)event_call->data;

	DEFINE_FIELD(unsigned long, func, FIELD_STRING_FUNC, 0);
	DEFINE_FIELD(unsigned long, ret_ip, FIELD_STRING_RETIP, 0);

	for (i = 0; i < tk->tp.nr_args; i++) {
		struct probe_arg *parg = &tk->tp.args[i];

		ret = trace_define_field(event_call, parg->type->fmttype,
					 parg->name,
					 sizeof(field) + parg->offset,
					 parg->type->size,
					 parg->type->is_signed,
					 FILTER_OTHER);
		if (ret)
			return ret;
	}
	return 0;
}
