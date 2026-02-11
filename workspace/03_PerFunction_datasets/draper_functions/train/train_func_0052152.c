ocfs2_mark_dead_nodes(struct ocfs2_super *osb)
{
	unsigned int node_num;
	int status, i;
	u32 gen;
	struct buffer_head *bh = NULL;
	struct ocfs2_dinode *di;


	for (i = 0; i < osb->max_slots; i++) {

		status = ocfs2_read_journal_inode(osb, i, &bh, NULL);
		if (status) {
			mlog_errno(status);
			goto bail;
		}
		di = (struct ocfs2_dinode *)bh->b_data;
		gen = ocfs2_get_recovery_generation(di);
		brelse(bh);
		bh = NULL;

		spin_lock(&osb->osb_lock);
		osb->slot_recovery_generations[i] = gen;

		trace_ocfs2_mark_dead_nodes(i,
					    osb->slot_recovery_generations[i]);

		if (i == osb->slot_num) {
			spin_unlock(&osb->osb_lock);
			continue;
		}

		status = ocfs2_slot_to_node_num_locked(osb, i, &node_num);
		if (status == -ENOENT) {
			spin_unlock(&osb->osb_lock);
			continue;
		}

		if (__ocfs2_recovery_map_test(osb, node_num)) {
			spin_unlock(&osb->osb_lock);
			continue;
		}
		spin_unlock(&osb->osb_lock);


		status = ocfs2_trylock_journal(osb, i);
		if (!status) {


			ocfs2_recovery_thread(osb, node_num);
		} else if ((status < 0) && (status != -EAGAIN)) {
			mlog_errno(status);
			goto bail;
		}
	}

	status = 0;
bail:
	return status;
}
