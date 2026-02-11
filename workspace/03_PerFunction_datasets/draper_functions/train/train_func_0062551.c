devfreq_add_device(struct device *dev,
				   struct devfreq_dev_profile *profile,
				   const char *governor_name,
				   void *data)
{
	struct devfreq *devfreq;
	struct devfreq_governor *governor;
	int err = 0;

	if (!dev || !profile || !governor_name) {
		dev_err(dev, "%s: Invalid parameters.\n", __func__);
		return ERR_PTR(-EINVAL);
	}

	mutex_lock(&devfreq_list_lock);
	devfreq = find_device_devfreq(dev);
	mutex_unlock(&devfreq_list_lock);
	if (!IS_ERR(devfreq)) {
		dev_err(dev, "%s: Unable to create devfreq for the device. It already has one.\n", __func__);
		err = -EINVAL;
		goto err_out;
	}

	devfreq = kzalloc(sizeof(struct devfreq), GFP_KERNEL);
	if (!devfreq) {
		dev_err(dev, "%s: Unable to create devfreq for the device\n",
			__func__);
		err = -ENOMEM;
		goto err_out;
	}

	mutex_init(&devfreq->lock);
	mutex_lock(&devfreq->lock);
	devfreq->dev.parent = dev;
	devfreq->dev.class = devfreq_class;
	devfreq->dev.release = devfreq_dev_release;
	devfreq->profile = profile;
	strncpy(devfreq->governor_name, governor_name, DEVFREQ_NAME_LEN);
	devfreq->previous_freq = profile->initial_freq;
	devfreq->data = data;
	devfreq->nb.notifier_call = devfreq_notifier_call;

	devfreq->trans_table =	devm_kzalloc(dev, sizeof(unsigned int) *
						devfreq->profile->max_state *
						devfreq->profile->max_state,
						GFP_KERNEL);
	devfreq->time_in_state = devm_kzalloc(dev, sizeof(unsigned long) *
						devfreq->profile->max_state,
						GFP_KERNEL);
	devfreq->last_stat_updated = jiffies;

	dev_set_name(&devfreq->dev, "%s", dev_name(dev));
	err = device_register(&devfreq->dev);
	if (err) {
		put_device(&devfreq->dev);
		mutex_unlock(&devfreq->lock);
		goto err_out;
	}

	mutex_unlock(&devfreq->lock);

	mutex_lock(&devfreq_list_lock);
	list_add(&devfreq->node, &devfreq_list);

	governor = find_devfreq_governor(devfreq->governor_name);
	if (!IS_ERR(governor))
		devfreq->governor = governor;
	if (devfreq->governor)
		err = devfreq->governor->event_handler(devfreq,
					DEVFREQ_GOV_START, NULL);
	mutex_unlock(&devfreq_list_lock);
	if (err) {
		dev_err(dev, "%s: Unable to start governor for the device\n",
			__func__);
		goto err_init;
	}

	return devfreq;

err_init:
	list_del(&devfreq->node);
	device_unregister(&devfreq->dev);
	kfree(devfreq);
err_out:
	return ERR_PTR(err);
}
