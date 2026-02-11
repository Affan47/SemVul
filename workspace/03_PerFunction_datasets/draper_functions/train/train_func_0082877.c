node_read_cpumap(struct device *dev, bool list, char *buf)
{
	struct node *node_dev = to_node(dev);
	const struct cpumask *mask = cpumask_of_node(node_dev->dev.id);


	BUILD_BUG_ON((NR_CPUS/32 * 9) > (PAGE_SIZE-1));

	return cpumap_print_to_pagebuf(list, buf, mask);
}
