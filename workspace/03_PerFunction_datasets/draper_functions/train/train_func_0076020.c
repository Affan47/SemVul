sriov_numvfs_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	int ret;
	u16 num_vfs;

	ret = kstrtou16(buf, 0, &num_vfs);
	if (ret < 0)
		return ret;

	if (num_vfs > pci_sriov_get_totalvfs(pdev))
		return -ERANGE;

	if (num_vfs == pdev->sriov->num_VFs)
		return count;


	if (!pdev->driver || !pdev->driver->sriov_configure) {
		dev_info(&pdev->dev, "Driver doesn't support SRIOV configuration via sysfs\n");
		return -ENOSYS;
	}

	if (num_vfs == 0) {

		ret = pdev->driver->sriov_configure(pdev, 0);
		if (ret < 0)
			return ret;
		return count;
	}


	if (pdev->sriov->num_VFs) {
		dev_warn(&pdev->dev, "%d VFs already enabled. Disable before enabling %d VFs\n",
			 pdev->sriov->num_VFs, num_vfs);
		return -EBUSY;
	}

	ret = pdev->driver->sriov_configure(pdev, num_vfs);
	if (ret < 0)
		return ret;

	if (ret != num_vfs)
		dev_warn(&pdev->dev, "%d VFs requested; only %d enabled\n",
			 num_vfs, ret);

	return count;
}
