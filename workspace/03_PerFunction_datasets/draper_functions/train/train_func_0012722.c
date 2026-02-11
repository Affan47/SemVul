isl_schedule_plain_is_equal(__isl_keep isl_schedule *schedule1,
	__isl_keep isl_schedule *schedule2)
{
	if (!schedule1 || !schedule2)
		return -1;
	if (schedule1 == schedule2)
		return 1;
	return isl_schedule_tree_plain_is_equal(schedule1->root,
						schedule2->root);
}
