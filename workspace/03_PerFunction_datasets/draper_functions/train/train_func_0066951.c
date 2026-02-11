alloc_interval(struct compilation_unit *cu, struct var_info *var)
{
	struct live_interval *interval = arena_alloc(cu->arena, sizeof *interval);

	if (interval) {
		interval->var_info = var;
		interval->reg = MACH_REG_UNASSIGNED;
		interval->next_child = NULL;
		interval->prev_child = NULL;
		interval->spill_slot = NULL;
		interval->spill_parent = NULL;
		interval->spill_reload_reg.interval = interval;
		interval->spill_reload_reg.vm_type = var->vm_type;
		INIT_LIST_HEAD(&interval->interval_node);
		INIT_LIST_HEAD(&interval->use_positions);
		INIT_LIST_HEAD(&interval->range_list);
		INIT_LIST_HEAD(&interval->expired_range_list);
		interval->flags = 0;
	}
	return interval;
}
