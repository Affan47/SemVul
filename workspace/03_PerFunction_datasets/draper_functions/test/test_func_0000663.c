spidev_compat_ioc_message(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	struct spi_ioc_transfer __user	*u_ioc;
	int				retval = 0;
	struct spidev_data		*spidev;
	struct spi_device		*spi;
	unsigned			n_ioc, n;
	struct spi_ioc_transfer		*ioc;

	u_ioc = (struct spi_ioc_transfer __user *) compat_ptr(arg);
	if (!access_ok(VERIFY_READ, u_ioc, _IOC_SIZE(cmd)))
		return -EFAULT;


	spidev = filp->private_data;
	spin_lock_irq(&spidev->spi_lock);
	spi = spi_dev_get(spidev->spi);
	spin_unlock_irq(&spidev->spi_lock);

	if (spi == NULL)
		return -ESHUTDOWN;


	mutex_lock(&spidev->buf_lock);


	ioc = spidev_get_ioc_message(cmd, u_ioc, &n_ioc);
	if (IS_ERR(ioc)) {
		retval = PTR_ERR(ioc);
		goto done;
	}
	if (!ioc)
		goto done;


	for (n = 0; n < n_ioc; n++) {
		ioc[n].rx_buf = (uintptr_t) compat_ptr(ioc[n].rx_buf);
		ioc[n].tx_buf = (uintptr_t) compat_ptr(ioc[n].tx_buf);
	}


	retval = spidev_message(spidev, ioc, n_ioc);
	kfree(ioc);

done:
	mutex_unlock(&spidev->buf_lock);
	spi_dev_put(spi);
	return retval;
}
