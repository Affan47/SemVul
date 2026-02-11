__ocfs2_recovery_map_test(struct ocfs2_super *osb,
				     unsigned int node_num)
{
	int i;
	struct ocfs2_recovery_map *rm = osb->recovery_map;

	assert_spin_locked(&osb->osb_lock);

	for (i = 0; i < rm->rm_used; i++) {
		if (rm->rm_entries[i] == node_num)
			return 1;
	}

	return 0;
}
