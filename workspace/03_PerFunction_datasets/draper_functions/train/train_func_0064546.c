megasas_mgmt_ioctl_aen(struct file *file, unsigned long arg)
{
	struct megasas_instance *instance;
	struct megasas_aen aen;
	int error;
	int i;
	unsigned long flags;
	u32 wait_time = MEGASAS_RESET_WAIT_TIME;

	if (file->private_data != file) {
		printk(KERN_DEBUG "megasas: fasync_helper was not "
		       "called first\n");
		return -EINVAL;
	}

	if (copy_from_user(&aen, (void __user *)arg, sizeof(aen)))
		return -EFAULT;

	instance = megasas_lookup_instance(aen.host_no);

	if (!instance)
		return -ENODEV;

	if (atomic_read(&instance->adprecovery) == MEGASAS_HW_CRITICAL_ERROR) {
		return -ENODEV;
	}

	if (instance->unload == 1) {
		return -ENODEV;
	}

	for (i = 0; i < wait_time; i++) {

		spin_lock_irqsave(&instance->hba_lock, flags);
		if (atomic_read(&instance->adprecovery) == MEGASAS_HBA_OPERATIONAL) {
			spin_unlock_irqrestore(&instance->hba_lock,
						flags);
			break;
		}

		spin_unlock_irqrestore(&instance->hba_lock, flags);

		if (!(i % MEGASAS_RESET_NOTICE_INTERVAL)) {
			dev_notice(&instance->pdev->dev, "waiting for"
				"controller reset to finish\n");
		}

		msleep(1000);
	}

	spin_lock_irqsave(&instance->hba_lock, flags);
	if (atomic_read(&instance->adprecovery) != MEGASAS_HBA_OPERATIONAL) {
		spin_unlock_irqrestore(&instance->hba_lock, flags);
		dev_err(&instance->pdev->dev, "timed out while waiting"
				"for HBA to recover\n");
		return -ENODEV;
	}
	spin_unlock_irqrestore(&instance->hba_lock, flags);

	mutex_lock(&instance->reset_mutex);
	error = megasas_register_aen(instance, aen.seq_num,
				     aen.class_locale_word);
	mutex_unlock(&instance->reset_mutex);
	return error;
}
