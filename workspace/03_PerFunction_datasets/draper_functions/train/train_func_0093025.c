xfs_alloc_ioend(
	struct inode		*inode,
	unsigned int		type)
{
	xfs_ioend_t		*ioend;

	ioend = mempool_alloc(xfs_ioend_pool, GFP_NOFS);


	atomic_set(&ioend->io_remaining, 1);
	ioend->io_error = 0;
	ioend->io_list = NULL;
	ioend->io_type = type;
	ioend->io_inode = inode;
	ioend->io_buffer_head = NULL;
	ioend->io_buffer_tail = NULL;
	ioend->io_offset = 0;
	ioend->io_size = 0;
	ioend->io_append_trans = NULL;

	INIT_WORK(&ioend->io_work, xfs_end_io);
	return ioend;
}
