pcifront_try_connect(struct pcifront_device *pdev)
{
	int err = -EFAULT;
	int i, num_roots, len;
	char str[64];
	unsigned int domain, bus;


	if (xenbus_read_driver_state(pdev->xdev->nodename) !=
	    XenbusStateInitialised)
		goto out;

	err = pcifront_connect_and_init_dma(pdev);
	if (err && err != -EEXIST) {
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error setting up PCI Frontend");
		goto out;
	}

	err = xenbus_scanf(XBT_NIL, pdev->xdev->otherend,
			   "root_num", "%d", &num_roots);
	if (err == -ENOENT) {
		xenbus_dev_error(pdev->xdev, err,
				 "No PCI Roots found, trying 0000:00");
		err = pcifront_scan_root(pdev, 0, 0);
		if (err) {
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root 0000:00");
			goto out;
		}
		num_roots = 0;
	} else if (err != 1) {
		if (err == 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of PCI roots");
		goto out;
	}

	for (i = 0; i < num_roots; i++) {
		len = snprintf(str, sizeof(str), "root-%d", i);
		if (unlikely(len >= (sizeof(str) - 1))) {
			err = -ENOMEM;
			goto out;
		}

		err = xenbus_scanf(XBT_NIL, pdev->xdev->otherend, str,
				   "%x:%x", &domain, &bus);
		if (err != 2) {
			if (err >= 0)
				err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading PCI root %d", i);
			goto out;
		}

		err = pcifront_scan_root(pdev, domain, bus);
		if (err) {
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error scanning PCI root %04x:%02x",
					 domain, bus);
			goto out;
		}
	}

	err = xenbus_switch_state(pdev->xdev, XenbusStateConnected);

out:
	return err;
}
