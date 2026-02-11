clk_core_get_parent_by_index(struct clk_core *core,
							 u8 index)
{
	if (!core || index >= core->num_parents)
		return NULL;
	else if (!core->parents)
		return clk_core_lookup(core->parent_names[index]);
	else if (!core->parents[index])
		return core->parents[index] =
			clk_core_lookup(core->parent_names[index]);
	else
		return core->parents[index];
}
