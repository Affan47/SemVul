__dlm_put_mle(struct dlm_master_list_entry *mle)
{
	struct dlm_ctxt *dlm;
	dlm = mle->dlm;

	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&dlm->master_lock);
	if (!atomic_read(&mle->mle_refs.refcount)) {


		mlog(ML_ERROR, "bad mle: %p\n", mle);
		dlm_print_one_mle(mle);
		BUG();
	} else
		kref_put(&mle->mle_refs, dlm_mle_release);
}
