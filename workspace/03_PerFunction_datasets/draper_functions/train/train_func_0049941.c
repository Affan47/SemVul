ocfs2_orphan_scan_start(struct ocfs2_super *osb)
{
	struct ocfs2_orphan_scan *os;

	os = &osb->osb_orphan_scan;
	os->os_scantime = CURRENT_TIME;
	if (ocfs2_is_hard_readonly(osb) || ocfs2_mount_local(osb))
		atomic_set(&os->os_state, ORPHAN_SCAN_INACTIVE);
	else {
		atomic_set(&os->os_state, ORPHAN_SCAN_ACTIVE);
		queue_delayed_work(ocfs2_wq, &os->os_orphan_scan_work,
				   ocfs2_orphan_scan_timeout());
	}
}
