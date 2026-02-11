bcma_of_fill_device(struct platform_device *parent,
				struct bcma_device *core)
{
	struct device_node *node;

	node = bcma_of_find_child_device(parent, core);
	if (node)
		core->dev.of_node = node;

	core->irq = bcma_of_get_irq(parent, core, 0);
}
