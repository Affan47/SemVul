dlm_create_debugfs_subroot(struct dlm_ctxt *dlm)
{
	dlm->dlm_debugfs_subroot = debugfs_create_dir(dlm->name,
						      dlm_debugfs_root);
	if (!dlm->dlm_debugfs_subroot) {
		mlog_errno(-ENOMEM);
		goto bail;
	}

	dlm->dlm_debug_ctxt = kzalloc(sizeof(struct dlm_debug_ctxt),
				      GFP_KERNEL);
	if (!dlm->dlm_debug_ctxt) {
		mlog_errno(-ENOMEM);
		goto bail;
	}
	kref_init(&dlm->dlm_debug_ctxt->debug_refcnt);

	return 0;
bail:
	dlm_destroy_debugfs_subroot(dlm);
	return -ENOMEM;
}
