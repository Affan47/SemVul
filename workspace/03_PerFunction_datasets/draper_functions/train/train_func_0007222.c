nilfs_direct_gather_data(struct nilfs_bmap *direct,
				    __u64 *keys, __u64 *ptrs, int nitems)
{
	__u64 key;
	__u64 ptr;
	int n;

	if (nitems > NILFS_DIRECT_NBLOCKS)
		nitems = NILFS_DIRECT_NBLOCKS;
	n = 0;
	for (key = 0; key < nitems; key++) {
		ptr = nilfs_direct_get_ptr(direct, key);
		if (ptr != NILFS_BMAP_INVALID_PTR) {
			keys[n] = key;
			ptrs[n] = ptr;
			n++;
		}
	}
	return n;
}
