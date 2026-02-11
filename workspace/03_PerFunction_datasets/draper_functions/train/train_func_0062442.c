ath10k_debug_fw_reset_stats_read(struct file *file,
						char __user *user_buf,
						size_t count, loff_t *ppos)
{
	struct ath10k *ar = file->private_data;
	int ret, len, buf_len;
	char *buf;

	buf_len = 500;
	buf = kmalloc(buf_len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	spin_lock_bh(&ar->data_lock);

	len = 0;
	len += scnprintf(buf + len, buf_len - len,
			 "fw_crash_counter\t\t%d\n", ar->stats.fw_crash_counter);
	len += scnprintf(buf + len, buf_len - len,
			 "fw_warm_reset_counter\t\t%d\n",
			 ar->stats.fw_warm_reset_counter);
	len += scnprintf(buf + len, buf_len - len,
			 "fw_cold_reset_counter\t\t%d\n",
			 ar->stats.fw_cold_reset_counter);

	spin_unlock_bh(&ar->data_lock);

	ret = simple_read_from_buffer(user_buf, count, ppos, buf, len);

	kfree(buf);

	return ret;
}
