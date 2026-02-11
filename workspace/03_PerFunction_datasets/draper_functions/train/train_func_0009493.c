fs_iterator__free_frame(fs_iterator_frame *ff)
{
	size_t i;
	git_path_with_stat *path;

	git_vector_foreach(&ff->entries, i, path)
		git__free(path);
	git_vector_free(&ff->entries);
	git__free(ff);
}
