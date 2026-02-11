write_index(git_index *index, git_filebuf *file)
{
	int error = GIT_SUCCESS;
	git_oid hash_final;

	struct index_header header;

	int is_extended = 1;

	assert(index && file);

	header.signature = htonl(INDEX_HEADER_SIG);
	header.version = htonl(is_extended ? INDEX_VERSION_NUMBER : INDEX_VERSION_NUMBER_EXT);
	header.entry_count = htonl(index->entries.length);

	git_filebuf_write(file, &header, sizeof(struct index_header));

	error = write_entries(index, file);
	if (error < GIT_SUCCESS)
		return error;


	git_filebuf_hash(&hash_final, file);


	git_filebuf_write(file, hash_final.id, GIT_OID_RAWSZ);

	return error;
}
