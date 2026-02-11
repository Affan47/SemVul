ipmi_poll(struct file *file, poll_table *wait)
{
	struct ipmi_file_private *priv = file->private_data;
	unsigned int             mask = 0;
	unsigned long            flags;

	poll_wait(file, &priv->wait, wait);

	spin_lock_irqsave(&priv->recv_msg_lock, flags);

	if (!list_empty(&(priv->recv_msgs)))
		mask |= (POLLIN | POLLRDNORM);

	spin_unlock_irqrestore(&priv->recv_msg_lock, flags);

	return mask;
}
