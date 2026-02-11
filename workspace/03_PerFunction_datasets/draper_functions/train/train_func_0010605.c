dlm_free_ctxt_mem(struct dlm_ctxt *dlm)
{
	dlm_destroy_debugfs_subroot(dlm);

	if (dlm->lockres_hash)
		dlm_free_pagevec((void **)dlm->lockres_hash, DLM_HASH_PAGES);

	if (dlm->master_hash)
		dlm_free_pagevec((void **)dlm->master_hash, DLM_HASH_PAGES);

	kfree(dlm->name);
	kfree(dlm);
}
