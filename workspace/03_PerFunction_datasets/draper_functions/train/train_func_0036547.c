epoll_create_set(struct pollset *pset)
{
	int err;

	pset->impl=g_slice_new0(struct impl_data);
	pset->impl->fd=epoll_create(8);
	if (pset->impl->fd == -1) {
		err=errno;
		g_slice_free(struct impl_data, pset->impl);
		return err;
	}
	err=set_cloexec(pset->impl->fd);
	if (err) {
		close(pset->impl->fd);
		g_slice_free(struct impl_data, pset->impl);
		return err;
	}
	return 0;
}
