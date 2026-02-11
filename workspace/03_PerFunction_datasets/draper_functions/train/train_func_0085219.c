s3fwrn5_i2c_irq_thread_fn(int irq, void *phy_id)
{
	struct s3fwrn5_i2c_phy *phy = phy_id;
	int ret = 0;

	if (!phy || !phy->ndev) {
		WARN_ON_ONCE(1);
		return IRQ_NONE;
	}

	mutex_lock(&phy->mutex);

	if (phy->irq_skip)
		goto out;

	switch (phy->mode) {
	case S3FWRN5_MODE_NCI:
	case S3FWRN5_MODE_FW:
		ret = s3fwrn5_i2c_read(phy);
		break;
	case S3FWRN5_MODE_COLD:
		ret = -EREMOTEIO;
		break;
	}

out:
	mutex_unlock(&phy->mutex);

	return IRQ_HANDLED;
}
