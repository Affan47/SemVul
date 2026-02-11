bq27xxx_battery_poll(struct work_struct *work)
{
	struct bq27xxx_device_info *di =
			container_of(work, struct bq27xxx_device_info,
				     work.work);

	bq27xxx_battery_update(di);

	if (poll_interval > 0) {

		set_timer_slack(&di->work.timer, poll_interval * HZ / 4);
		schedule_delayed_work(&di->work, poll_interval * HZ);
	}
}
