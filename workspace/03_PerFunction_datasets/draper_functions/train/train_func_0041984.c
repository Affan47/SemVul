put_pid_ns(struct pid_namespace *ns)
{
	struct pid_namespace *parent;

	while (ns != &init_pid_ns) {
		parent = ns->parent;
		if (!kref_put(&ns->kref, free_pid_ns))
			break;
		ns = parent;
	}
}
