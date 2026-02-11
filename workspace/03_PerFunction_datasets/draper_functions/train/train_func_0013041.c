store_delta(git_indexer_stream *idx)
{
	struct delta_info *delta;

	delta = git__calloc(1, sizeof(struct delta_info));
	GITERR_CHECK_ALLOC(delta);
	delta->delta_off = idx->entry_start;

	if (git_vector_insert(&idx->deltas, delta) < 0)
		return -1;

	return 0;
}
