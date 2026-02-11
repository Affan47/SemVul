__dlm_unlink_mle(struct dlm_ctxt *dlm, struct dlm_master_list_entry *mle)
{
	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&dlm->master_lock);

	if (!hlist_unhashed(&mle->master_hash_node))
		hlist_del_init(&mle->master_hash_node);
}
