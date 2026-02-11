attr_syntax_return_locking_optional(struct asyntaxinfo *asi, PRBool use_lock)
{
	int locked = 0;
	if(use_lock) {
		AS_LOCK_READ(name2asi_lock);
		locked = 1;
	}
	if ( NULL != asi ) {
		PRBool		delete_it = PR_FALSE;
		if ( 0 == PR_AtomicDecrement( &asi->asi_refcnt )) {
			delete_it = asi->asi_marked_for_delete;
		}

		if (delete_it) {
			if ( asi->asi_marked_for_delete ) {
				if(use_lock) {
					AS_UNLOCK_READ(name2asi_lock);
					AS_LOCK_WRITE(name2asi_lock);
				}


				attr_syntax_free(asi);
				if(use_lock) {
					AS_UNLOCK_WRITE(name2asi_lock);
					locked = 0;
				}
			}
		}
	}
	if(locked) {
		AS_UNLOCK_READ(name2asi_lock);
	}
}
