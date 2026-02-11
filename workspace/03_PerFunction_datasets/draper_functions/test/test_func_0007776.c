git_indexer_free(git_indexer *idx)
{
	unsigned int i;
	struct entry *e;
	struct git_pack_entry *pe;

	if (idx == NULL)
		return;

	p_close(idx->pack->mwf.fd);
	git_mwindow_file_deregister(&idx->pack->mwf);
	git_vector_foreach(&idx->objects, i, e)
		git__free(e);
	git_vector_free(&idx->objects);
	git_vector_foreach(&idx->pack->cache, i, pe)
		git__free(pe);
	git_vector_free(&idx->pack->cache);
	git__free(idx->pack);
	git__free(idx);
}
