free_queue(struct fs_dev *dev, struct queue *txq)
{
	func_enter ();

	write_fs (dev, Q_SA(txq->offset), 0);
	write_fs (dev, Q_EA(txq->offset), 0);
	write_fs (dev, Q_RP(txq->offset), 0);
	write_fs (dev, Q_WP(txq->offset), 0);


	fs_dprintk (FS_DEBUG_ALLOC, "Free queue: %p\n", txq->sa);
	kfree (txq->sa);

	func_exit ();
}
