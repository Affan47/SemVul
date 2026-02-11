allocate_ftrace_ops(struct trace_array *tr)
{
	struct ftrace_ops *ops;

	ops = kzalloc(sizeof(*ops), GFP_KERNEL);
	if (!ops)
		return -ENOMEM;


	ops->func = function_trace_call;
	ops->flags = FTRACE_OPS_FL_RECURSION_SAFE;

	tr->ops = ops;
	ops->private = tr;
	return 0;
}
