dev_pm_qos_remove_notifier(struct device *dev,
			       struct notifier_block *notifier)
{
	int retval = 0;

	mutex_lock(&dev_pm_qos_mtx);


	if (!IS_ERR_OR_NULL(dev->power.qos))
		retval = blocking_notifier_chain_unregister(dev->power.qos->resume_latency.notifiers,
							    notifier);

	mutex_unlock(&dev_pm_qos_mtx);
	return retval;
}
