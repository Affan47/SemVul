iwl_dbgfs_plcp_delta_write(struct file *file,
					const char __user *user_buf,
					size_t count, loff_t *ppos) {

	struct iwl_priv *priv = file->private_data;
	char buf[8];
	int buf_size;
	int plcp;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) -  1);
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;
	if (sscanf(buf, "%d", &plcp) != 1)
		return -EINVAL;
	if ((plcp < IWL_MAX_PLCP_ERR_THRESHOLD_MIN) ||
		(plcp > IWL_MAX_PLCP_ERR_THRESHOLD_MAX))
		priv->plcp_delta_threshold =
			IWL_MAX_PLCP_ERR_THRESHOLD_DISABLE;
	else
		priv->plcp_delta_threshold = plcp;
	return count;
}
