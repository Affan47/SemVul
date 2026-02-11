bch_journal(struct cache_set *c,
		      struct keylist *keys,
		      struct closure *parent)
{
	struct journal_write *w;
	atomic_t *ret;

	if (!CACHE_SYNC(&c->sb))
		return NULL;

	w = journal_wait_for_write(c, bch_keylist_nkeys(keys));

	memcpy(bset_bkey_last(w->data), keys->keys, bch_keylist_bytes(keys));
	w->data->keys += bch_keylist_nkeys(keys);

	ret = &fifo_back(&c->journal.pin);
	atomic_inc(ret);

	if (parent) {
		closure_wait(&w->wait, parent);
		journal_try_write(c);
	} else if (!w->dirty) {
		w->dirty = true;
		schedule_delayed_work(&c->journal.work,
				      msecs_to_jiffies(c->journal_delay_ms));
		spin_unlock(&c->journal.lock);
	} else {
		spin_unlock(&c->journal.lock);
	}


	return ret;
}
