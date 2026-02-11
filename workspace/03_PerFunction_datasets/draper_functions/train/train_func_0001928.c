shm_mq_get_sender(shm_mq *mq)
{
	volatile shm_mq *vmq = mq;
	PGPROC	   *sender;

	SpinLockAcquire(&mq->mq_mutex);
	sender = vmq->mq_sender;
	SpinLockRelease(&mq->mq_mutex);

	return sender;
}
