cache_del(struct cache *c, const char *key)
{
	pthread_rwlock_wrlock(&c->lock);
	struct entry *e = entry_for_key(c, key);

	if (e->in_use == IN_USE && strcmp(e->key, key) == 0) {
		free(e->key);
		e->key = NULL;
		e->value = NULL;
		e->in_use = REMOVED;
		pthread_rwlock_unlock(&c->lock);
		return true;
	}

	pthread_rwlock_unlock(&c->lock);
	return false;
}
