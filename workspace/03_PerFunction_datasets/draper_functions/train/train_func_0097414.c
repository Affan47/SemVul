guess_boot_cpuid(struct node *tree)
{
	struct node *cpus, *bootcpu;
	struct property *reg;

	cpus = get_node_by_path(tree, "/cpus");
	if (!cpus)
		return 0;


	bootcpu = cpus->children;
	if (!bootcpu)
		return 0;

	reg = get_property(bootcpu, "reg");
	if (!reg || (reg->val.len != sizeof(uint32_t)))
		return 0;


	return propval_cell(reg);
}
