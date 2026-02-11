hsc_release(struct inode *inode __maybe_unused, struct file *file)
{
	struct hsc_channel *channel = file->private_data;
	struct hsc_client_data *cl_data = channel->cl_data;

	mutex_lock(&cl_data->lock);
	file->private_data = NULL;
	if (test_and_clear_bit(HSC_CH_WLINE, &channel->flags))
		hsi_stop_tx(channel->cl);
	__hsc_port_release(cl_data);
	hsc_reset_list(channel, &channel->rx_msgs_queue);
	hsc_reset_list(channel, &channel->tx_msgs_queue);
	hsc_reset_list(channel, &channel->free_msgs_list);
	clear_bit(HSC_CH_READ, &channel->flags);
	clear_bit(HSC_CH_WRITE, &channel->flags);
	clear_bit(HSC_CH_OPEN, &channel->flags);
	wake_up(&channel->rx_wait);
	wake_up(&channel->tx_wait);
	mutex_unlock(&cl_data->lock);

	return 0;
}
