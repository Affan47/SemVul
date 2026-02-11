complexmode_enter(struct sem_array *sma)
{
	int i;
	struct sem *sem;

	if (sma->complex_mode)  {

		return;
	}


	smp_store_mb(sma->complex_mode, true);

	for (i = 0; i < sma->sem_nsems; i++) {
		sem = sma->sem_base + i;
		spin_unlock_wait(&sem->lock);
	}
	ipc_smp_acquire__after_spin_is_unlocked();
}
