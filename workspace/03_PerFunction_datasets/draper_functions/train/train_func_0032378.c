PR_DestroyRWLock(PRRWLock *rwlock)
{
#if defined(HAVE_UNIX98_RWLOCK) || defined(HAVE_UI_RWLOCK)
	int err;
	err = RWLOCK_DESTROY(&rwlock->rw_lock);
	PR_ASSERT(err == 0);
#else
	PR_ASSERT(rwlock->rw_reader_cnt == 0);
	PR_DestroyCondVar(rwlock->rw_reader_waitq);
	PR_DestroyCondVar(rwlock->rw_writer_waitq);
	PR_DestroyLock(rwlock->rw_lock);
#endif
	if (rwlock->rw_name != NULL)
		PR_Free(rwlock->rw_name);
    PR_DELETE(rwlock);
}
