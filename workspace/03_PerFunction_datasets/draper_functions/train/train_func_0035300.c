pnp_activate_dev(struct pnp_dev *dev)
{
	int error;

	if (dev->active)
		return 0;


	if (pnp_auto_config_dev(dev))
		return -EBUSY;

	error = pnp_start_dev(dev);
	if (error)
		return error;

	dev->active = 1;
	return 0;
}
