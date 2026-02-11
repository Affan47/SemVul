iio_read_first_n_kfifo(struct iio_buffer *r,
			   size_t n, char __user *buf)
{
	int ret, copied;
	struct iio_kfifo *kf = iio_to_kfifo(r);

	if (mutex_lock_interruptible(&kf->user_lock))
		return -ERESTARTSYS;

	if (!kfifo_initialized(&kf->kf) || n < kfifo_esize(&kf->kf))
		ret = -EINVAL;
	else
		ret = kfifo_to_user(&kf->kf, buf, n, &copied);
	mutex_unlock(&kf->user_lock);
	if (ret < 0)
		return ret;

	return copied;
}
