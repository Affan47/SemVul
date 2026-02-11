fat_cache_merge(struct inode *inode,
					 struct fat_cache_id *new)
{
	struct fat_cache *p;

	list_for_each_entry(p, &MSDOS_I(inode)->cache_lru, cache_list) {

		if (p->fcluster == new->fcluster) {
			BUG_ON(p->dcluster != new->dcluster);
			if (new->nr_contig > p->nr_contig)
				p->nr_contig = new->nr_contig;
			return p;
		}
	}
	return NULL;
}
