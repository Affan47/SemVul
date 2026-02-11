ocfs2_complete_quota_recovery(struct ocfs2_super *osb)
{
	if (osb->quota_rec) {
		ocfs2_queue_recovery_completion(osb->journal,
						osb->slot_num,
						NULL,
						NULL,
						osb->quota_rec,
						ORPHAN_NEED_TRUNCATE);
		osb->quota_rec = NULL;
	}
}
