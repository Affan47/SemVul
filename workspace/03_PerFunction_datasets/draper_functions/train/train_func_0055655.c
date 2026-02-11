sst_ipc_init(struct sst_generic_ipc *ipc)
{
	int ret;

	INIT_LIST_HEAD(&ipc->tx_list);
	INIT_LIST_HEAD(&ipc->rx_list);
	INIT_LIST_HEAD(&ipc->empty_list);
	init_waitqueue_head(&ipc->wait_txq);

	ret = msg_empty_list_init(ipc);
	if (ret < 0)
		return -ENOMEM;


	init_kthread_worker(&ipc->kworker);
	ipc->tx_thread = kthread_run(kthread_worker_fn,
					&ipc->kworker, "%s",
					dev_name(ipc->dev));
	if (IS_ERR(ipc->tx_thread)) {
		dev_err(ipc->dev, "error: failed to create message TX task\n");
		ret = PTR_ERR(ipc->tx_thread);
		kfree(ipc->msg);
		return ret;
	}

	init_kthread_work(&ipc->kwork, ipc_tx_msgs);
	return 0;
}
