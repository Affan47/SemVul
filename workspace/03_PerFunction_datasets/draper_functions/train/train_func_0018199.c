ocfs2_recovery_exit(struct ocfs2_super *osb)
{
	struct ocfs2_recovery_map *rm;


	mutex_lock(&osb->recovery_lock);
	osb->disable_recovery = 1;
	mutex_unlock(&osb->recovery_lock);
	wait_event(osb->recovery_event, !ocfs2_recovery_thread_running(osb));


	flush_workqueue(ocfs2_wq);


	rm = osb->recovery_map;


	kfree(rm);
}
