macvtap_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *file = iocb->ki_filp;
	struct macvtap_queue *q = file->private_data;
	ssize_t len = iov_iter_count(to), ret;

	ret = macvtap_do_read(q, to, file->f_flags & O_NONBLOCK);
	ret = min_t(ssize_t, ret, len);
	if (ret > 0)
		iocb->ki_pos = ret;
	return ret;
}
