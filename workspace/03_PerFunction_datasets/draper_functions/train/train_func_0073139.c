blkif_copy_from_grant(unsigned long gfn, unsigned int offset,
				  unsigned int len, void *data)
{
	struct copy_from_grant *info = data;
	char *shared_data;

	const struct blk_shadow *s = info->s;

	shared_data = kmap_atomic(s->grants_used[info->grant_idx]->page);

	memcpy(info->bvec_data + info->bvec_offset,
	       shared_data + offset, len);

	info->bvec_offset += len;
	info->grant_idx++;

	kunmap_atomic(shared_data);
}
