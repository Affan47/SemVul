git_index_write(git_index *index)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	struct stat indexst;
	int error;

	git_vector_sort(&index->entries);

	if ((error = git_filebuf_open(
			 &file, index->index_file_path, GIT_FILEBUF_HASH_CONTENTS)) < 0)
		return error;

	if ((error = write_index(index, &file)) < 0) {
		git_filebuf_cleanup(&file);
		return error;
	}

	if ((error = git_filebuf_commit(&file, GIT_INDEX_FILE_MODE)) < 0)
		return error;

	if (p_stat(index->index_file_path, &indexst) == 0) {
		index->last_modified = indexst.st_mtime;
		index->on_disk = 1;
	}

	return 0;
}
