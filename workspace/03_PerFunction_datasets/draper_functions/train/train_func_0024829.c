physmap_set_vpp(struct map_info *map, int state)
{
	struct platform_device *pdev;
	struct physmap_flash_data *physmap_data;
	struct physmap_flash_info *info;
	unsigned long flags;

	pdev = (struct platform_device *)map->map_priv_1;
	physmap_data = dev_get_platdata(&pdev->dev);

	if (!physmap_data->set_vpp)
		return;

	info = platform_get_drvdata(pdev);

	spin_lock_irqsave(&info->vpp_lock, flags);
	if (state) {
		if (++info->vpp_refcnt == 1)
			physmap_data->set_vpp(pdev, 1);
	} else {
		if (--info->vpp_refcnt == 0)
			physmap_data->set_vpp(pdev, 0);
	}
	spin_unlock_irqrestore(&info->vpp_lock, flags);
}
