index_free(git_index *index)
{
	git_index_entry *e;
	git_index_reuc_entry *reuc;
	unsigned int i;

	git_index_clear(index);
	git_vector_foreach(&index->entries, i, e) {
		index_entry_free(e);
	}
	git_vector_free(&index->entries);
	git_vector_foreach(&index->reuc, i, reuc) {
		index_entry_reuc_free(reuc);
	}
	git_vector_free(&index->reuc);

	git__free(index->index_file_path);
	git__free(index);
}
