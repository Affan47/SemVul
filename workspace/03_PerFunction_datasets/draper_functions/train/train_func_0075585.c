activate_dev(char *devname, char *resname, struct pnp_dev *dev)
{
	int err;

	err = pnp_device_attach(dev);
	if (err < 0)
		return(NULL);

	if((err = pnp_activate_dev(dev)) < 0) {
		printk(KERN_ERR "ad1848: %s %s config failed (out of resources?)[%d]\n", devname, resname, err);

		pnp_device_detach(dev);

		return(NULL);
	}
	audio_activated = 1;
	return(dev);
}
