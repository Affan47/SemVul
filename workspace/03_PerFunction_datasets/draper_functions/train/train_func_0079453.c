get_path_common(struct fuse *f, fuse_ino_t nodeid, const char *name,
			   char **path, struct node **wnode)
{
	int err;

	pthread_mutex_lock(&f->lock);
	err = try_get_path(f, nodeid, name, path, wnode, true);
	if (err == -EAGAIN) {
		struct lock_queue_element qe = {
			.nodeid1 = nodeid,
			.name1 = name,
			.path1 = path,
			.wnode1 = wnode,
		};
		debug_path(f, "QUEUE PATH", nodeid, name, !!wnode);
		err = wait_path(f, &qe);
		debug_path(f, "DEQUEUE PATH", nodeid, name, !!wnode);
	}
	pthread_mutex_unlock(&f->lock);

	return err;
}
