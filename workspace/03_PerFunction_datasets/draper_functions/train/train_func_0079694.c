alloc_trace_uprobe(const char *group, const char *event, int nargs, bool is_ret)
{
	struct trace_uprobe *tu;

	if (!event || !is_good_name(event))
		return ERR_PTR(-EINVAL);

	if (!group || !is_good_name(group))
		return ERR_PTR(-EINVAL);

	tu = kzalloc(SIZEOF_TRACE_UPROBE(nargs), GFP_KERNEL);
	if (!tu)
		return ERR_PTR(-ENOMEM);

	tu->tp.call.class = &tu->tp.class;
	tu->tp.call.name = kstrdup(event, GFP_KERNEL);
	if (!tu->tp.call.name)
		goto error;

	tu->tp.class.system = kstrdup(group, GFP_KERNEL);
	if (!tu->tp.class.system)
		goto error;

	INIT_LIST_HEAD(&tu->list);
	INIT_LIST_HEAD(&tu->tp.files);
	tu->consumer.handler = uprobe_dispatcher;
	if (is_ret)
		tu->consumer.ret_handler = uretprobe_dispatcher;
	init_trace_uprobe_filter(&tu->filter);
	return tu;

error:
	kfree(tu->tp.call.name);
	kfree(tu);

	return ERR_PTR(-ENOMEM);
}
