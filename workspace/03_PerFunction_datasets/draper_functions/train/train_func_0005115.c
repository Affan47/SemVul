fr_fifo_create(int max_entries, fr_fifo_free_t freeNode)
{
	fr_fifo_t *fi;

	if ((max_entries < 2) || (max_entries > (1024 * 1024))) return NULL;

	fi = malloc(sizeof(*fi));
	if (!fi) return NULL;

	memset(fi, 0, sizeof(*fi));

	fi->max_entries = max_entries;
	fi->freeNode = freeNode;

	return fi;
}
