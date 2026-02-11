can_precede_at_level(int shared_level, int target_level)
{
	if (shared_level < target_level)
		return 0;
	if ((target_level % 2) && shared_level > target_level)
		return 0;
	return 1;
}
