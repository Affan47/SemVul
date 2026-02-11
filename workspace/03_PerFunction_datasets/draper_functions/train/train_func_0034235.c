set_member_enabled(struct member *mem)
{
	if ((mem->depsfailed == HARD_FAILURE) || (mem->conflictsfailed == HARD_FAILURE))
		return;

	if ((mem->enabled) || (mem->is_separator))
		return;

	enable_member(mem);
	mem->was_defaulted = 0;
	changes_made++;

	while (calc_dep_failures(1, 0) || calc_conflict_failures(1, 0));
}
