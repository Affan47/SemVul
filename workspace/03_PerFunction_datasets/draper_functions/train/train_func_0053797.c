ocfs2_dlm_shutdown(struct ocfs2_super *osb,
			int hangup_pending)
{
	ocfs2_drop_osb_locks(osb);


	if (osb->dc_task) {
		kthread_stop(osb->dc_task);
		osb->dc_task = NULL;
	}

	ocfs2_lock_res_free(&osb->osb_super_lockres);
	ocfs2_lock_res_free(&osb->osb_rename_lockres);
	ocfs2_lock_res_free(&osb->osb_nfs_sync_lockres);
	ocfs2_lock_res_free(&osb->osb_orphan_scan.os_lockres);

	ocfs2_cluster_disconnect(osb->cconn, hangup_pending);
	osb->cconn = NULL;

	ocfs2_dlm_shutdown_debug(osb);
}
