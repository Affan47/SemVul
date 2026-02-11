hash_find(hash_t *tbl, char *key)
{
	hash_entry_t *tmp;
	unsigned int sig;

	if (tbl->hash_type == STRING_HASH_KEY)
		sig = hash_string(key);
	else
		sig = (unsigned int) key;
	pthread_mutex_lock(&tbl->lock);
	assert(hash_check(tbl));
	while (tbl->operator_wait_count || tbl->lock_status < 0) {
		tbl->get_wait_count++;
		pthread_cond_wait(&tbl->get_cv, &tbl->lock);
		tbl->get_wait_count--;
	}
	tmp = tbl->table[ sig % tbl->size];
	if (tbl->hash_type == STRING_HASH_KEY) {
		for ( ;tmp != NULL; tmp = tmp->next_entry) {
			if (sig == tmp->hash_signature && strcmp(tmp->key, key) == 0)
				break;
		}
	} else {
		for (; tmp != NULL; tmp = tmp->next_entry) {
			if (tmp->key == key)
				break;
		}
	}
	if (tmp) {
		if (tmp->num_waiters || (tmp->status & ENTRY_LOCKED)) {
			hash_waiter_t wait;

			wait.wakeup = 0;
			wait.entry = tmp;
			pthread_cond_init(&wait.cv, NULL);
			tmp->num_waiters++;
			ll_enqueue(&tmp->waiters, &wait.list);
			while (wait.wakeup == 0)
				pthread_cond_wait(&wait.cv, &tbl->lock);
			tmp->num_waiters--;
			ll_dequeue(&tmp->waiters);
			pthread_cond_destroy(&wait.cv);
		}
		tmp->status |= ENTRY_LOCKED;
		tmp->holder = pthread_self();
		tbl->lock_status++;
		assert(hash_check(tbl));
		pthread_mutex_unlock(&tbl->lock);
		return (&tmp->data);
	}
	assert(hash_check(tbl));
	pthread_mutex_unlock(&tbl->lock);
	return (NULL);
}
