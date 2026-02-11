ipmi_open(struct inode *inode, struct file *file)
{
	int                      if_num = iminor(inode);
	int                      rv;
	struct ipmi_file_private *priv;


	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_lock(&ipmi_mutex);
	priv->file = file;

	rv = ipmi_create_user(if_num,
			      &ipmi_hndlrs,
			      priv,
			      &(priv->user));
	if (rv) {
		kfree(priv);
		goto out;
	}

	file->private_data = priv;

	spin_lock_init(&(priv->recv_msg_lock));
	INIT_LIST_HEAD(&(priv->recv_msgs));
	init_waitqueue_head(&priv->wait);
	priv->fasync_queue = NULL;
	mutex_init(&priv->recv_mutex);


	priv->default_retries = -1;
	priv->default_retry_time_ms = 0;

out:
	mutex_unlock(&ipmi_mutex);
	return rv;
}
