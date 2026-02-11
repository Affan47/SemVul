dlm_debug_shutdown(struct dlm_ctxt *dlm)
{
	struct dlm_debug_ctxt *dc = dlm->dlm_debug_ctxt;

	if (dc) {
		debugfs_remove(dc->debug_purgelist_dentry);
		debugfs_remove(dc->debug_mle_dentry);
		debugfs_remove(dc->debug_lockres_dentry);
		debugfs_remove(dc->debug_state_dentry);
		dlm_debug_put(dc);
	}
}
