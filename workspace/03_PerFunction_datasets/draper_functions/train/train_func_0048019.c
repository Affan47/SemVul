_xfer_secondary_pool(struct entropy_store *r, size_t nbytes)
{
	__u32	tmp[OUTPUT_POOL_WORDS];


	int rsvd_bytes = r->limit ? 0 : random_read_wakeup_bits / 4;
	int bytes = nbytes;


	bytes = max_t(int, bytes, random_read_wakeup_bits / 8);

	bytes = min_t(int, bytes, sizeof(tmp));

	trace_xfer_secondary_pool(r->name, bytes * 8, nbytes * 8,
				  ENTROPY_BITS(r), ENTROPY_BITS(r->pull));
	bytes = extract_entropy(r->pull, tmp, bytes,
				random_read_wakeup_bits / 8, rsvd_bytes);
	mix_pool_bytes(r, tmp, bytes);
	credit_entropy_bits(r, bytes*8);
}
