ocfs2_complete_mount_recovery(struct ocfs2_super *osb)
{
	struct ocfs2_journal *journal = osb->journal;

	if (ocfs2_is_hard_readonly(osb))
		return;


	ocfs2_queue_recovery_completion(journal, osb->slot_num,
					osb->local_alloc_copy, NULL, NULL,
					ORPHAN_NEED_TRUNCATE);
	ocfs2_schedule_truncate_log_flush(osb, 0);

	osb->local_alloc_copy = NULL;
	osb->dirty = 0;


	ocfs2_replay_map_set_state(osb, REPLAY_NEEDED);
	ocfs2_queue_replay_slots(osb, ORPHAN_NEED_TRUNCATE);
	ocfs2_free_replay_slots(osb);
}
