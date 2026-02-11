rev_free_dirs (void)
{
    unsigned long   hash;

    for (hash = 0; hash < REV_DIR_HASH; hash++) {
	rev_dir_hash    **bucket = &buckets[hash];
	rev_dir_hash	*h;

	while ((h = *bucket)) {
	    *bucket = h->next;
	    free (h);
	}
    }
    if (rds) {
	free (rds);
	rds = NULL;
	sds = 0;
    }
}
