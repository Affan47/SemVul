alloc_chunk(git_revwalk *walk)
{
	void *chunk;

	chunk = git__calloc(COMMITS_PER_CHUNK, CHUNK_STEP);
	if (chunk == NULL)
		return GIT_ENOMEM;

	walk->chunk_size = 0;
	return git_vector_insert(&walk->memory_alloc, chunk);
}
