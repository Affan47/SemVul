cram_index_free(cram_fd *fd) {
    int i;

    if (!fd->index)
	return;

    for (i = 0; i < fd->index_sz; i++) {
	cram_index_free_recurse(&fd->index[i]);
    }
    free(fd->index);

    fd->index = NULL;
}
