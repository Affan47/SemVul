hotkey_poll_setup(const bool may_warn)
{
	const u32 poll_driver_mask = hotkey_driver_mask & hotkey_source_mask;
	const u32 poll_user_mask = hotkey_user_mask & hotkey_source_mask;

	if (hotkey_poll_freq > 0 &&
	    (poll_driver_mask ||
	     (poll_user_mask && tpacpi_inputdev->users > 0))) {
		if (!tpacpi_hotkey_task) {
			tpacpi_hotkey_task = kthread_run(hotkey_kthread,
					NULL, TPACPI_NVRAM_KTHREAD_NAME);
			if (IS_ERR(tpacpi_hotkey_task)) {
				tpacpi_hotkey_task = NULL;
				pr_err("could not create kernel thread "
				       "for hotkey polling\n");
			}
		}
	} else {
		hotkey_poll_stop_sync();
		if (may_warn && (poll_driver_mask || poll_user_mask) &&
		    hotkey_poll_freq == 0) {
			pr_notice("hot keys 0x%08x and/or events 0x%08x "
				  "require polling, which is currently "
				  "disabled\n",
				  poll_user_mask, poll_driver_mask);
		}
	}
}
