tick_resume_local(void)
{
	struct tick_device *td = this_cpu_ptr(&tick_cpu_device);
	bool broadcast = tick_resume_check_broadcast();

	clockevents_tick_resume(td->evtdev);
	if (!broadcast) {
		if (td->mode == TICKDEV_MODE_PERIODIC)
			tick_setup_periodic(td->evtdev, 0);
		else
			tick_resume_oneshot();
	}
}
