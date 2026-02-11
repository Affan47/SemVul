mmc_pm_notify(struct notifier_block *notify_block,
					unsigned long mode, void *unused)
{
	struct mmc_host *host = container_of(
		notify_block, struct mmc_host, pm_notify);
	unsigned long flags;
	int err = 0;

	switch (mode) {
	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
	case PM_RESTORE_PREPARE:
		spin_lock_irqsave(&host->lock, flags);
		host->rescan_disable = 1;
		spin_unlock_irqrestore(&host->lock, flags);
		cancel_delayed_work_sync(&host->detect);

		if (!host->bus_ops)
			break;


		if (host->bus_ops->pre_suspend)
			err = host->bus_ops->pre_suspend(host);
		if (!err)
			break;


		host->bus_ops->remove(host);
		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_power_off(host);
		mmc_release_host(host);
		host->pm_flags = 0;
		break;

	case PM_POST_SUSPEND:
	case PM_POST_HIBERNATION:
	case PM_POST_RESTORE:

		spin_lock_irqsave(&host->lock, flags);
		host->rescan_disable = 0;
		spin_unlock_irqrestore(&host->lock, flags);
		_mmc_detect_change(host, 0, false);

	}

	return 0;
}
