w1_process_cb(struct w1_master *dev, struct w1_async_cmd *async_cmd)
{
	struct w1_cb_node *node = container_of(async_cmd, struct w1_cb_node,
		async);
	u16 mlen = node->msg->len;
	u16 len;
	int err = 0;
	struct w1_slave *sl = node->sl;
	struct w1_netlink_cmd *cmd = (struct w1_netlink_cmd *)node->msg->data;

	mutex_lock(&dev->bus_mutex);
	dev->priv = node->block;
	if (sl && w1_reset_select_slave(sl))
		err = -ENODEV;
	node->block->cur_msg = node->msg;

	while (mlen && !err) {
		if (cmd->len + sizeof(struct w1_netlink_cmd) > mlen) {
			err = -E2BIG;
			break;
		}

		if (sl)
			err = w1_process_command_slave(sl, cmd);
		else
			err = w1_process_command_master(dev, cmd);
		w1_netlink_check_send(node->block);

		w1_netlink_queue_status(node->block, node->msg, cmd, err);
		err = 0;

		len = sizeof(*cmd) + cmd->len;
		cmd = (struct w1_netlink_cmd *)((u8 *)cmd + len);
		mlen -= len;
	}

	if (!cmd || err)
		w1_netlink_queue_status(node->block, node->msg, cmd, err);


	if (sl)
		w1_unref_slave(sl);
	else
		atomic_dec(&dev->refcnt);
	dev->priv = NULL;
	mutex_unlock(&dev->bus_mutex);

	mutex_lock(&dev->list_mutex);
	list_del(&async_cmd->async_entry);
	mutex_unlock(&dev->list_mutex);

	w1_unref_block(node->block);
}
