velocity_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *of_id;
	const struct velocity_info_tbl *info;
	int irq;

	of_id = of_match_device(velocity_of_ids, &pdev->dev);
	if (!of_id)
		return -EINVAL;
	info = of_id->data;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (!irq)
		return -EINVAL;

	return velocity_probe(&pdev->dev, irq, info, BUS_PLATFORM);
}
