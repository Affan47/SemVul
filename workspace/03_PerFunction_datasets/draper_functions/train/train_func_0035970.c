hsc_write(struct file *file, const char __user *buf, size_t len,
						loff_t *ppos __maybe_unused)
{
	struct hsc_channel *channel = file->private_data;
	struct hsi_msg *msg;
	ssize_t ret;

	if ((len == 0) || !IS_ALIGNED(len, sizeof(u32)))
		return -EINVAL;
	if (len > max_data_size)
		len = max_data_size;
	if (channel->ch >= channel->cl->tx_cfg.num_hw_channels)
		return -ECHRNG;
	if (test_and_set_bit(HSC_CH_WRITE, &channel->flags))
		return -EBUSY;
	msg = hsc_get_first_msg(channel, &channel->free_msgs_list);
	if (!msg) {
		clear_bit(HSC_CH_WRITE, &channel->flags);
		return -ENOSPC;
	}
	if (copy_from_user(sg_virt(msg->sgt.sgl), (void __user *)buf, len)) {
		ret = -EFAULT;
		goto out;
	}
	hsc_msg_len_set(msg, len);
	msg->complete = hsc_tx_completed;
	msg->destructor = hsc_tx_msg_destructor;
	ret = hsi_async_write(channel->cl, msg);
	if (ret < 0)
		goto out;

	ret = wait_event_interruptible(channel->tx_wait,
					!list_empty(&channel->tx_msgs_queue));
	if (ret < 0) {
		clear_bit(HSC_CH_WRITE, &channel->flags);
		hsi_flush(channel->cl);
		return -EINTR;
	}

	msg = hsc_get_first_msg(channel, &channel->tx_msgs_queue);
	if (msg) {
		if (msg->status == HSI_STATUS_ERROR)
			ret = -EIO;
		else
			ret = hsc_msg_len_get(msg);

		hsc_add_tail(channel, msg, &channel->free_msgs_list);
	}
out:
	clear_bit(HSC_CH_WRITE, &channel->flags);

	return ret;
}
