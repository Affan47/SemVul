fuse_iqueue_init(struct fuse_iqueue *fiq)
{
	memset(fiq, 0, sizeof(struct fuse_iqueue));
	init_waitqueue_head(&fiq->waitq);
	INIT_LIST_HEAD(&fiq->pending);
	INIT_LIST_HEAD(&fiq->interrupts);
	fiq->forget_list_tail = &fiq->forget_list_head;
	fiq->connected = 1;
}
