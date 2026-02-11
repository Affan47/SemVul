ocfs2_recovery_map_clear(struct ocfs2_super *osb,
				     unsigned int node_num)
{
	int i;
	struct ocfs2_recovery_map *rm = osb->recovery_map;

	spin_lock(&osb->osb_lock);

	for (i = 0; i < rm->rm_used; i++) {
		if (rm->rm_entries[i] == node_num)
			break;
	}

	if (i < rm->rm_used) {

		memmove(&(rm->rm_entries[i]), &(rm->rm_entries[i + 1]),
			(rm->rm_used - i - 1) * sizeof(unsigned int));
		rm->rm_used--;
	}

	spin_unlock(&osb->osb_lock);
}
