nvm_ctl_ioctl(struct file *file, uint cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;

	switch (cmd) {
	case NVM_INFO:
		return nvm_ioctl_info(file, argp);
	case NVM_GET_DEVICES:
		return nvm_ioctl_get_devices(file, argp);
	case NVM_DEV_CREATE:
		return nvm_ioctl_dev_create(file, argp);
	case NVM_DEV_REMOVE:
		return nvm_ioctl_dev_remove(file, argp);
	case NVM_DEV_INIT:
		return nvm_ioctl_dev_init(file, argp);
	case NVM_DEV_FACTORY:
		return nvm_ioctl_dev_factory(file, argp);
	}
	return 0;
}
