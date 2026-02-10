fuse_ll_destroy(void *data)
{
	struct fuse_ll *f = (struct fuse_ll *) data;
	struct fuse_ll_pipe *llp;

	if (f->got_init && !f->got_destroy) {
		if (f->op.destroy)
			f->op.destroy(f->userdata);
	}
	llp = pthread_getspecific(f->pipe_key);
	if (llp != NULL)
		fuse_ll_pipe_free(llp);
	pthread_key_delete(f->pipe_key);
	pthread_mutex_destroy(&f->lock);
	free(f->cuse_data);
	free(f);
}
