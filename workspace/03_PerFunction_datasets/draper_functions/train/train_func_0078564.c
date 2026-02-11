auxdev_read(struct file *file, char __user *buf, size_t count,
			   loff_t *offset)
{
	size_t bytes_pending, num_bytes_processed = 0;
	struct drm_dp_aux_dev *aux_dev = file->private_data;
	ssize_t res = 0;

	if (!atomic_inc_not_zero(&aux_dev->usecount))
		return -ENODEV;

	bytes_pending = min((loff_t)count, AUX_MAX_OFFSET - (*offset));

	if (!access_ok(VERIFY_WRITE, buf, bytes_pending)) {
		res = -EFAULT;
		goto out;
	}

	while (bytes_pending > 0) {
		uint8_t localbuf[DP_AUX_MAX_PAYLOAD_BYTES];
		ssize_t todo = min_t(size_t, bytes_pending, sizeof(localbuf));

		if (signal_pending(current)) {
			res = num_bytes_processed ?
				num_bytes_processed : -ERESTARTSYS;
			goto out;
		}

		res = drm_dp_dpcd_read(aux_dev->aux, *offset, localbuf, todo);
		if (res <= 0) {
			res = num_bytes_processed ? num_bytes_processed : res;
			goto out;
		}
		if (__copy_to_user(buf + num_bytes_processed, localbuf, res)) {
			res = num_bytes_processed ?
				num_bytes_processed : -EFAULT;
			goto out;
		}
		bytes_pending -= res;
		*offset += res;
		num_bytes_processed += res;
		res = num_bytes_processed;
	}

out:
	atomic_dec(&aux_dev->usecount);
	wake_up_atomic_t(&aux_dev->usecount);
	return res;
}
