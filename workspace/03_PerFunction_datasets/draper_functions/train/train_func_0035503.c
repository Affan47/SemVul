user_recover_done(void *arg, struct dlm_slot *slots,
		int num_slots, int our_slot,
		uint32_t generation)
{
	struct ocfs2_cluster_connection *conn = arg;
	struct ocfs2_live_connection *lc = conn->cc_private;
	int i;

	for (i = 0; i < num_slots; i++)
		if (slots[i].slot == our_slot) {
			atomic_set(&lc->oc_this_node, slots[i].nodeid);
			break;
		}

	lc->oc_our_slot = our_slot;
	wake_up(&lc->oc_wait);
}
