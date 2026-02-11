register_lock_class(struct lockdep_map *lock, unsigned int subclass, int force)
{
	struct lockdep_subclass_key *key;
	struct list_head *hash_head;
	struct lock_class *class;

	DEBUG_LOCKS_WARN_ON(!irqs_disabled());

	class = look_up_lock_class(lock, subclass);
	if (likely(class))
		goto out_set_class_cache;


	if (!static_obj(lock->key)) {
		debug_locks_off();
		printk("INFO: trying to register non-static key.\n");
		printk("the code is fine but needs lockdep annotation.\n");
		printk("turning off the locking correctness validator.\n");
		dump_stack();

		return NULL;
	}

	key = lock->key->subkeys + subclass;
	hash_head = classhashentry(key);

	if (!graph_lock()) {
		return NULL;
	}


	list_for_each_entry_rcu(class, hash_head, hash_entry) {
		if (class->key == key)
			goto out_unlock_set;
	}


	if (nr_lock_classes >= MAX_LOCKDEP_KEYS) {
		if (!debug_locks_off_graph_unlock()) {
			return NULL;
		}

		print_lockdep_off("BUG: MAX_LOCKDEP_KEYS too low!");
		dump_stack();
		return NULL;
	}
	class = lock_classes + nr_lock_classes++;
	debug_atomic_inc(nr_unused_locks);
	class->key = key;
	class->name = lock->name;
	class->subclass = subclass;
	INIT_LIST_HEAD(&class->lock_entry);
	INIT_LIST_HEAD(&class->locks_before);
	INIT_LIST_HEAD(&class->locks_after);
	class->name_version = count_matching_names(class);


	list_add_tail_rcu(&class->hash_entry, hash_head);


	list_add_tail_rcu(&class->lock_entry, &all_lock_classes);

	if (verbose(class)) {
		graph_unlock();

		printk("\nnew class %p: %s", class->key, class->name);
		if (class->name_version > 1)
			printk("#%d", class->name_version);
		printk("\n");
		dump_stack();

		if (!graph_lock()) {
			return NULL;
		}
	}
out_unlock_set:
	graph_unlock();

out_set_class_cache:
	if (!subclass || force)
		lock->class_cache[0] = class;
	else if (subclass < NR_LOCKDEP_CACHING_CLASSES)
		lock->class_cache[subclass] = class;


	if (DEBUG_LOCKS_WARN_ON(class->subclass != subclass))
		return NULL;

	return class;
}
