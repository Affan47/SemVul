jbd2_commit_block_csum_verify(journal_t *j, void *buf)
{
	struct commit_header *h;
	__be32 provided;
	__u32 calculated;

	if (!jbd2_journal_has_csum_v2or3(j))
		return 1;

	h = buf;
	provided = h->h_chksum[0];
	h->h_chksum[0] = 0;
	calculated = jbd2_chksum(j, j->j_csum_seed, buf, j->j_blocksize);
	h->h_chksum[0] = provided;

	return provided == cpu_to_be32(calculated);
}
