index_free(git_index *index)
{
	git_index_entry *e;
	unsigned int i;

	git_index_clear(index);
	git_vector_foreach(&index->entries, i, e) {
		index_entry_free(e);
	}
	git_vector_free(&index->entries);
	git_vector_foreach(&index->unmerged, i, e) {
		index_entry_free(e);
	}
	git_vector_free(&index->unmerged);

	git__free(index->index_file_path);
	git__free(index);
}
