ocfs2_orphan_scan_work(struct work_struct *work)
{
	struct ocfs2_orphan_scan *os;
	struct ocfs2_super *osb;

	os = container_of(work, struct ocfs2_orphan_scan,
			  os_orphan_scan_work.work);
	osb = os->os_osb;

	mutex_lock(&os->os_lock);
	ocfs2_queue_orphan_scan(osb);
	if (atomic_read(&os->os_state) == ORPHAN_SCAN_ACTIVE)
		queue_delayed_work(ocfs2_wq, &os->os_orphan_scan_work,
				      ocfs2_orphan_scan_timeout());
	mutex_unlock(&os->os_lock);
}
