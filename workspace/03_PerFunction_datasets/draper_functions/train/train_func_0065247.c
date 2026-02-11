tick_check_new_device(struct clock_event_device *newdev)
{
	struct clock_event_device *curdev;
	struct tick_device *td;
	int cpu;

	cpu = smp_processor_id();
	td = &per_cpu(tick_cpu_device, cpu);
	curdev = td->evtdev;


	if (!tick_check_percpu(curdev, newdev, cpu))
		goto out_bc;


	if (!tick_check_preferred(curdev, newdev))
		goto out_bc;

	if (!try_module_get(newdev->owner))
		return;


	if (tick_is_broadcast_device(curdev)) {
		clockevents_shutdown(curdev);
		curdev = NULL;
	}
	clockevents_exchange_device(curdev, newdev);
	tick_setup_device(td, newdev, cpu, cpumask_of(cpu));
	if (newdev->features & CLOCK_EVT_FEAT_ONESHOT)
		tick_oneshot_notify();
	return;

out_bc:


	tick_install_broadcast_device(newdev);
}
