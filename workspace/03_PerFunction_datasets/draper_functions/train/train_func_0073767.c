fuse_pqueue_init(struct fuse_pqueue *fpq)
{
	memset(fpq, 0, sizeof(struct fuse_pqueue));
	spin_lock_init(&fpq->lock);
	INIT_LIST_HEAD(&fpq->processing);
	INIT_LIST_HEAD(&fpq->io);
	fpq->connected = 1;
}
