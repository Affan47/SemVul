max_gen_clk_remove(struct platform_device *pdev, int num_init)
{
	struct device *dev = pdev->dev.parent;

	if (dev->of_node)
		of_clk_del_provider(dev->of_node);

	return 0;
}
