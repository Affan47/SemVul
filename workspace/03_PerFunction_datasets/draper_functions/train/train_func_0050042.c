read_extension(git_index *index, const char *buffer, size_t buffer_size)
{
	const struct index_extension *source;
	struct index_extension dest;
	size_t total_size;

	source = (const struct index_extension *)(buffer);

	memcpy(dest.signature, source->signature, 4);
	dest.extension_size = ntohl(source->extension_size);

	total_size = dest.extension_size + sizeof(struct index_extension);

	if (buffer_size - total_size < INDEX_FOOTER_SIZE)
		return 0;


	if (dest.signature[0] >= 'A' && dest.signature[0] <= 'Z') {

		if (memcmp(dest.signature, INDEX_EXT_TREECACHE_SIG, 4) == 0) {
			if (git_tree_cache_read(&index->tree, buffer + 8, dest.extension_size) < 0)
				return 0;
		} else if (memcmp(dest.signature, INDEX_EXT_UNMERGED_SIG, 4) == 0) {
			if (read_reuc(index, buffer + 8, dest.extension_size) < 0)
				return 0;
		} else if (memcmp(dest.signature, INDEX_EXT_CONFLICT_NAME_SIG, 4) == 0) {
			if (read_conflict_names(index, buffer + 8, dest.extension_size) < 0)
				return 0;
		}


	} else {


		return 0;
	}

	return total_size;
}
