dma_async_device_unregister(struct dma_device *device)
{
	struct dma_chan *chan;

	mutex_lock(&dma_list_mutex);
	list_del_rcu(&device->global_node);
	dma_channel_rebalance();
	mutex_unlock(&dma_list_mutex);

	list_for_each_entry(chan, &device->channels, device_node) {
		WARN_ONCE(chan->client_count,
			  "%s called while %d clients hold a reference\n",
			  __func__, chan->client_count);
		mutex_lock(&dma_list_mutex);
		chan->dev->chan = NULL;
		mutex_unlock(&dma_list_mutex);
		device_unregister(&chan->dev->device);
		free_percpu(chan->local);
	}
}
