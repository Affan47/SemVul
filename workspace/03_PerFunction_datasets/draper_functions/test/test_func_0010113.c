ldr_init_hash(struct db_main *db)
{
	struct db_salt *current;
	int threshold, size;

	threshold = password_hash_thresholds[0];
	if (db->format && (db->format->params.flags & FMT_BS)) {


		threshold = 5 * ARCH_BITS / ARCH_BITS_LOG + 1;
	}

	if ((current = db->salts))
	do {
		size = -1;
		if (current->count >= threshold && mem_saving_level < 3)
			for (size = PASSWORD_HASH_SIZES - 1; size >= 0; size--)
				if (current->count >=
				    password_hash_thresholds[size] &&
				    db->format->methods.binary_hash[size] &&
				    db->format->methods.binary_hash[size] !=
				    fmt_default_binary_hash)
					break;

		if (mem_saving_level >= 2)
			size--;

		current->hash_size = size;
		ldr_init_hash_for_salt(db, current);
	} while ((current = current->next));
}
