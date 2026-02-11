db_lru_insert(cache_entry* entry){
	assert(entry->lru_removed);
	assert(entry != db.lru_tail);
	assert(entry->lru_next == NULL);
	assert(entry->lru_prev == NULL);


	entry->lru_prev = db.lru_tail;
	if (db.lru_tail != NULL){
		assert(db.lru_tail->lru_next == NULL);
		db.lru_tail->lru_next = entry;
	}
	entry->lru_next = NULL;
	db.lru_tail = entry;
	if (db.lru_head == NULL){
		db.lru_head = entry;
	}

#ifdef DEBUG_BUILD
	entry->lru_removed = false;
#endif
}
