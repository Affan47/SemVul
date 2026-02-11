dev_mem_write(struct file *file, const char __user *user_buf,
		size_t count, loff_t *ppos)
{
	struct wl1271 *wl = file->private_data;
	struct wlcore_partition_set part, old_part;
	size_t bytes = count;
	int ret;
	char *buf;


	if (bytes % 4)
		return -EINVAL;

	if (*ppos % 4)
		return -EINVAL;


	bytes = min(bytes, WLCORE_MAX_BLOCK_SIZE);

	if (bytes == 0)
		return -EINVAL;

	memset(&part, 0, sizeof(part));
	part.mem.start = *ppos;
	part.mem.size = bytes;

	buf = kmalloc(bytes, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = copy_from_user(buf, user_buf, bytes);
	if (ret) {
		ret = -EFAULT;
		goto err_out;
	}

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state == WLCORE_STATE_OFF)) {
		ret = -EFAULT;
		goto skip_write;
	}


	wl1271_ps_elp_wakeup(wl);


	memcpy(&old_part, &wl->curr_part, sizeof(old_part));
	ret = wlcore_set_partition(wl, &part);
	if (ret < 0)
		goto part_err;

	ret = wlcore_raw_write(wl, 0, buf, bytes, false);
	if (ret < 0)
		goto write_err;

write_err:

	ret = wlcore_set_partition(wl, &old_part);
	if (ret < 0)
		goto part_err;

part_err:
	wl1271_ps_elp_sleep(wl);

skip_write:
	mutex_unlock(&wl->mutex);

	if (ret == 0)
		*ppos += bytes;

err_out:
	kfree(buf);

	return ((ret == 0) ? bytes : ret);
}
