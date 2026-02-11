erst_dbg_read(struct file *filp, char __user *ubuf,
			     size_t usize, loff_t *off)
{
	int rc, *pos;
	ssize_t len = 0;
	u64 id;

	if (*off)
		return -EINVAL;

	if (mutex_lock_interruptible(&erst_dbg_mutex) != 0)
		return -EINTR;

	pos = (int *)&filp->private_data;

retry_next:
	rc = erst_get_record_id_next(pos, &id);
	if (rc)
		goto out;

	if (id == APEI_ERST_INVALID_RECORD_ID) {


		len = 0;

		goto out;
	}
retry:
	rc = len = erst_read(id, erst_dbg_buf, erst_dbg_buf_len);

	if (rc == -ENOENT)
		goto retry_next;
	if (rc < 0)
		goto out;
	if (len > ERST_DBG_RECORD_LEN_MAX) {
		pr_warning(ERST_DBG_PFX
			   "Record (ID: 0x%llx) length is too long: %zd\n",
			   id, len);
		rc = -EIO;
		goto out;
	}
	if (len > erst_dbg_buf_len) {
		void *p;
		rc = -ENOMEM;
		p = kmalloc(len, GFP_KERNEL);
		if (!p)
			goto out;
		kfree(erst_dbg_buf);
		erst_dbg_buf = p;
		erst_dbg_buf_len = len;
		goto retry;
	}

	rc = -EINVAL;
	if (len > usize)
		goto out;

	rc = -EFAULT;
	if (copy_to_user(ubuf, erst_dbg_buf, len))
		goto out;
	rc = 0;
out:
	mutex_unlock(&erst_dbg_mutex);
	return rc ? rc : len;
}
