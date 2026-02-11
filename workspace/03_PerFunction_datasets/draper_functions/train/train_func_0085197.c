rocker_group_tbl_find(const struct rocker *rocker,
		      const struct rocker_group_tbl_entry *match)
{
	struct rocker_group_tbl_entry *found;

	hash_for_each_possible(rocker->group_tbl, found,
			       entry, match->group_id) {
		if (found->group_id == match->group_id)
			return found;
	}

	return NULL;
}
