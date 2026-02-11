pinctrl_init_device_debugfs(struct pinctrl_dev *pctldev)
{
	struct dentry *device_root;

	device_root = debugfs_create_dir(dev_name(pctldev->dev),
					 debugfs_root);
	pctldev->device_root = device_root;

	if (IS_ERR(device_root) || !device_root) {
		pr_warn("failed to create debugfs directory for %s\n",
			dev_name(pctldev->dev));
		return;
	}
	debugfs_create_file("pins", S_IFREG | S_IRUGO,
			    device_root, pctldev, &pinctrl_pins_ops);
	debugfs_create_file("pingroups", S_IFREG | S_IRUGO,
			    device_root, pctldev, &pinctrl_groups_ops);
	debugfs_create_file("gpio-ranges", S_IFREG | S_IRUGO,
			    device_root, pctldev, &pinctrl_gpioranges_ops);
	if (pctldev->desc->pmxops)
		pinmux_init_device_debugfs(device_root, pctldev);
	if (pctldev->desc->confops)
		pinconf_init_device_debugfs(device_root, pctldev);
}
