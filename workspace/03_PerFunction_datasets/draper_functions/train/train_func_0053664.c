index_conflict_data_eq_merge_diff(const struct merge_index_conflict_data *expected, git_merge_diff *actual)
{
	if (!index_entry_eq_merge_index_entry(&expected->ancestor.entry, &actual->ancestor_entry) ||
		!index_entry_eq_merge_index_entry(&expected->ours.entry, &actual->our_entry) ||
		!index_entry_eq_merge_index_entry(&expected->theirs.entry, &actual->their_entry))
		return 0;

	if (expected->ours.status != actual->our_status ||
		expected->theirs.status != actual->their_status)
		return 0;

	return 1;
}
