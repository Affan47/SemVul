ocfs2_recovery_map_set(struct ocfs2_super *osb,
				  unsigned int node_num)
{
	struct ocfs2_recovery_map *rm = osb->recovery_map;

	spin_lock(&osb->osb_lock);
	if (__ocfs2_recovery_map_test(osb, node_num)) {
		spin_unlock(&osb->osb_lock);
		return 1;
	}


	BUG_ON(rm->rm_used >= osb->max_slots);

	rm->rm_entries[rm->rm_used] = node_num;
	rm->rm_used++;
	spin_unlock(&osb->osb_lock);

	return 0;
}
