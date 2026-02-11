__dlm_queue_bast(struct dlm_ctxt *dlm, struct dlm_lock *lock)
{
	struct dlm_lock_resource *res;

	BUG_ON(!dlm);
	BUG_ON(!lock);

	assert_spin_locked(&dlm->ast_lock);

	res = lock->lockres;

	BUG_ON(!list_empty(&lock->bast_list));
	if (lock->bast_pending)
		mlog(0, "%s: res %.*s, lock %u:%llu, BAST getting flushed\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)));


	dlm_lock_get(lock);
	spin_lock(&lock->spinlock);
	list_add_tail(&lock->bast_list, &dlm->pending_basts);
	lock->bast_pending = 1;
	spin_unlock(&lock->spinlock);
}
