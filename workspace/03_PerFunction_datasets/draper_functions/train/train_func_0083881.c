__ocfs2_node_num_to_slot(struct ocfs2_slot_info *si,
				    unsigned int node_num)
{
	int i, ret = -ENOENT;

	for(i = 0; i < si->si_num_slots; i++) {
		if (si->si_slots[i].sl_valid &&
		    (node_num == si->si_slots[i].sl_node_num)) {
			ret = i;
			break;
		}
	}

	return ret;
}
