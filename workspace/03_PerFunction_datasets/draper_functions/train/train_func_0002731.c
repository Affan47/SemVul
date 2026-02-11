vhci_read(struct file *file,
			 char __user *buf, size_t count, loff_t *pos)
{
	struct vhci_data *data = file->private_data;
	struct sk_buff *skb;
	ssize_t ret = 0;

	while (count) {
		skb = skb_dequeue(&data->readq);
		if (skb) {
			ret = vhci_put_user(data, skb, buf, count);
			if (ret < 0)
				skb_queue_head(&data->readq, skb);
			else
				kfree_skb(skb);
			break;
		}

		if (file->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			break;
		}

		ret = wait_event_interruptible(data->read_wait,
					       !skb_queue_empty(&data->readq));
		if (ret < 0)
			break;
	}

	return ret;
}
