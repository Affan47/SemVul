fuse_dev_alloc(struct fuse_conn *fc)
{
	struct fuse_dev *fud;

	fud = kzalloc(sizeof(struct fuse_dev), GFP_KERNEL);
	if (fud) {
		fud->fc = fuse_conn_get(fc);
		fuse_pqueue_init(&fud->pq);

		spin_lock(&fc->lock);
		list_add_tail(&fud->entry, &fc->devices);
		spin_unlock(&fc->lock);
	}

	return fud;
}
