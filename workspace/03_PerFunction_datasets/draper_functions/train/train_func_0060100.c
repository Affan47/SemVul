schedule_set_options(
	__isl_take isl_schedule *schedule, struct options *options)
{
	enum isl_ast_loop_type type;

	if (!options->separate && !options->atomic)
		return schedule;

	type = options->separate ? isl_ast_loop_separate : isl_ast_loop_atomic;
	schedule = isl_schedule_map_schedule_node(schedule,
						&node_set_options, &type);

	return schedule;
}
