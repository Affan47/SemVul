tsi57x_probe(struct rio_dev *rdev, const struct rio_device_id *id)
{
	pr_debug("RIO: %s for %s\n", __func__, rio_name(rdev));

	spin_lock(&rdev->rswitch->lock);

	if (rdev->rswitch->ops) {
		spin_unlock(&rdev->rswitch->lock);
		return -EINVAL;
	}
	rdev->rswitch->ops = &tsi57x_switch_ops;

	if (rdev->do_enum) {

		rio_write_config_32(rdev, RIO_STD_RTE_DEFAULT_PORT,
				    RIO_INVALID_ROUTE);
	}

	spin_unlock(&rdev->rswitch->lock);
	return 0;
}
