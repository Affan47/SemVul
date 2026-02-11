unresolved(const struct traverse_info *info, struct name_entry n[3])
{
	struct merge_list *entry = NULL;

	if (unresolved_directory(info, n))
		return;


	entry = link_entry(3, info, n + 2, entry);
	entry = link_entry(2, info, n + 1, entry);
	entry = link_entry(1, info, n + 0, entry);

	add_merge_entry(entry);
}
