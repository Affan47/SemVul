symval_hash_search(ulong value)
{
	int index;
	struct syment *sp, *splo;

	index = SYMVAL_HASH_INDEX(value);

	if (!st->symval_hash[index].val_hash_head)
		return NULL;

	st->val_hash_searches += 1;
	st->val_hash_iterations += 1;

	if (st->symval_hash[index].val_hash_last->value <= value)
		sp = st->symval_hash[index].val_hash_last;
	else
		sp = st->symval_hash[index].val_hash_head;

	for (splo = NULL; sp; sp = sp->val_hash_next) {
		if (sp->value == value) {
			st->symval_hash[index].val_hash_last = sp;
			return sp;
		}

		if (sp->value > value)
			break;

		st->val_hash_iterations += 1;

		splo = sp;
	}

	if (splo)
		st->symval_hash[index].val_hash_last = splo;

	return splo;
}
