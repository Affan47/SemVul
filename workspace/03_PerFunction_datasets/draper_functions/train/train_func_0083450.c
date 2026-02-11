handle_command(const char *command, enum pool pool, const char *arg)
{
	switch (*command) {
	case 'a':
		if (!prefixcmp(command, "alloc ")) {
			uint32_t n = strtouint32(arg);
			printf("%"PRIu32"\n",
				pool == POOL_ONE ?
				one_alloc(n) : two_alloc(n));
			return;
		}
	case 'c':
		if (!prefixcmp(command, "commit ")) {
			pool == POOL_ONE ? one_commit() : two_commit();
			return;
		}
		if (!prefixcmp(command, "committed ")) {
			printf("%"PRIu32"\n",
				pool == POOL_ONE ?
				one_pool.committed : two_pool.committed);
			return;
		}
	case 'f':
		if (!prefixcmp(command, "free ")) {
			uint32_t n = strtouint32(arg);
			pool == POOL_ONE ? one_free(n) : two_free(n);
			return;
		}
	case 'n':
		if (!prefixcmp(command, "null ")) {
			printf("%"PRIu32"\n",
				pool == POOL_ONE ?
				one_offset(NULL) : two_offset(NULL));
			return;
		}
	case 'o':
		if (!prefixcmp(command, "offset ")) {
			uint32_t n = strtouint32(arg);
			printf("%"PRIu32"\n",
				pool == POOL_ONE ?
				one_offset(one_pointer(n)) :
				two_offset(two_pointer(n)));
			return;
		}
	case 'r':
		if (!prefixcmp(command, "reset ")) {
			pool == POOL_ONE ? one_reset() : two_reset();
			return;
		}
	case 's':
		if (!prefixcmp(command, "set ")) {
			uint32_t n = strtouint32(arg);
			if (pool == POOL_ONE)
				*one_pointer(n) = 1;
			else
				*two_pointer(n) = 1;
			return;
		}
	case 't':
		if (!prefixcmp(command, "test ")) {
			uint32_t n = strtouint32(arg);
			printf("%d\n", pool == POOL_ONE ?
				*one_pointer(n) : *two_pointer(n));
			return;
		}
	default:
		die("unrecognized command: %s", command);
	}
}
