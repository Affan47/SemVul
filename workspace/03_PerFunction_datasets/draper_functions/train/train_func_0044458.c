cxio_init_qpid_fifo(struct cxio_rdev *rdev_p)
{
	u32 i;

	spin_lock_init(&rdev_p->rscp->qpid_fifo_lock);

	if (kfifo_alloc(&rdev_p->rscp->qpid_fifo, T3_MAX_NUM_QP * sizeof(u32),
					      GFP_KERNEL))
		return -ENOMEM;

	for (i = 16; i < T3_MAX_NUM_QP; i++)
		if (!(i & rdev_p->qpmask))
			kfifo_in(&rdev_p->rscp->qpid_fifo,
				    (unsigned char *) &i, sizeof(u32));
	return 0;
}
