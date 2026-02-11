lis3lv02d_joystick_open(struct input_polled_dev *pidev)
{
	struct lis3lv02d *lis3 = pidev->private;

	if (lis3->pm_dev)
		pm_runtime_get_sync(lis3->pm_dev);

	if (lis3->pdata && lis3->whoami == WAI_8B && lis3->idev)
		atomic_set(&lis3->wake_thread, 1);


	lis3lv02d_joystick_poll(pidev);
}
