load_block_from_cache(BGZF *fp, int64_t block_address)
{
	khint_t k;
	cache_t *p;
	khash_t(cache) *h = (khash_t(cache)*)fp->cache;
	k = kh_get(cache, h, block_address);
	if (k == kh_end(h)) return 0;
	p = &kh_val(h, k);
	if (fp->block_length != 0) fp->block_offset = 0;
	fp->block_address = block_address;
	fp->block_length = p->size;
	memcpy(fp->uncompressed_block, p->block, BGZF_MAX_BLOCK_SIZE);
	if ( hseek(fp->fp, p->end_offset, SEEK_SET) < 0 )
    {

        fprintf(stderr,"Could not hseek to %"PRId64"\n", p->end_offset);
        exit(1);
    }
	return p->size;
}
