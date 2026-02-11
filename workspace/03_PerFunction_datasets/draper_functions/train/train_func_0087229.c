balloon_init_watcher(struct notifier_block *notifier,
				unsigned long event,
				void *data)
{
	int err;

	err = register_xenbus_watch(&target_watch);
	if (err)
		pr_err("Failed to set balloon watcher\n");

	return NOTIFY_DONE;
}
