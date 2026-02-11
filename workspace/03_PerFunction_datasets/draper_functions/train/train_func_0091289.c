deferred_probe_initcall(void)
{
	deferred_wq = create_singlethread_workqueue("deferwq");
	if (WARN_ON(!deferred_wq))
		return -ENOMEM;

	driver_deferred_probe_enable = true;
	driver_deferred_probe_trigger();

	flush_workqueue(deferred_wq);
	return 0;
}
