hvutil_transport_send(struct hvutil_transport *hvt, void *msg, int len,
			  void (*on_read_cb)(void))
{
	struct cn_msg *cn_msg;
	int ret = 0;

	if (hvt->mode == HVUTIL_TRANSPORT_INIT ||
	    hvt->mode == HVUTIL_TRANSPORT_DESTROY) {
		return -EINVAL;
	} else if (hvt->mode == HVUTIL_TRANSPORT_NETLINK) {
		cn_msg = kzalloc(sizeof(*cn_msg) + len, GFP_ATOMIC);
		if (!cn_msg)
			return -ENOMEM;
		cn_msg->id.idx = hvt->cn_id.idx;
		cn_msg->id.val = hvt->cn_id.val;
		cn_msg->len = len;
		memcpy(cn_msg->data, msg, len);
		ret = cn_netlink_send(cn_msg, 0, 0, GFP_ATOMIC);
		kfree(cn_msg);


		if (on_read_cb)
			on_read_cb();
		return ret;
	}

	mutex_lock(&hvt->lock);
	if (hvt->mode != HVUTIL_TRANSPORT_CHARDEV) {
		ret = -EINVAL;
		goto out_unlock;
	}

	if (hvt->outmsg) {

		ret = -EFAULT;
		goto out_unlock;
	}
	hvt->outmsg = kzalloc(len, GFP_KERNEL);
	if (hvt->outmsg) {
		memcpy(hvt->outmsg, msg, len);
		hvt->outmsg_len = len;
		hvt->on_read = on_read_cb;
		wake_up_interruptible(&hvt->outmsg_q);
	} else
		ret = -ENOMEM;
out_unlock:
	mutex_unlock(&hvt->lock);
	return ret;
}
