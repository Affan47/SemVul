allocate_blocked_reg(struct compilation_unit *cu,
				 struct live_interval *current,
				 struct list_head *active,
				 struct list_head *inactive,
				 struct pqueue *unhandled)
{
	unsigned long use_pos[NR_REGISTERS], block_pos[NR_REGISTERS];
	struct live_interval *it;
	int i;
	enum machine_reg reg;

	for (i = 0; i < NR_REGISTERS; i++) {
		use_pos[i] = LONG_MAX;
		block_pos[i] = LONG_MAX;
	}

	list_for_each_entry(it, active, interval_node) {
		unsigned long pos;

		if (interval_has_fixed_reg(it))
			continue;

		pos = next_use_pos(it, interval_start(current));
		set_use_pos(use_pos, it->reg, pos);
	}

	list_for_each_entry(it, inactive, interval_node) {
		unsigned long pos;

		if (interval_has_fixed_reg(it))
			continue;

		if (!reg_supports_type(it->reg, current->var_info->vm_type))
			continue;

		if (intervals_intersect(it, current)) {
			pos = next_use_pos(it, interval_start(current));
			set_use_pos(use_pos, it->reg, pos);
		}
	}

	list_for_each_entry(it, active, interval_node) {
		if (!interval_has_fixed_reg(it))
			continue;

		set_block_pos(block_pos, use_pos, it->reg, 0);
	}

	list_for_each_entry(it, inactive, interval_node) {
		if (!interval_has_fixed_reg(it))
			continue;

		if (!reg_supports_type(it->reg, current->var_info->vm_type))
			continue;

		if (intervals_intersect(it, current)) {
			unsigned long pos;

			pos = interval_intersection_start(it, current);
			set_block_pos(block_pos, use_pos, it->reg, pos);
		}
	}

	reg = pick_register(use_pos, current->var_info->vm_type);
	if (use_pos[reg] < next_use_pos(current, 0)) {
		unsigned long pos;


		pos = next_use_pos(current, interval_start(current));
		spill_interval(cu, current, pos, unhandled);
	} else {


		current->reg = reg;

		if (block_pos[reg] < interval_end(current))
			spill_interval(cu, current, block_pos[reg], unhandled);

		spill_all_intervals_intersecting(cu, current, reg, active,
						 inactive, unhandled);
	}
}
