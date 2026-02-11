storvsc_dev_remove(struct hv_device *device)
{
	struct storvsc_device *stor_device;
	unsigned long flags;

	stor_device = hv_get_drvdata(device);

	spin_lock_irqsave(&device->channel->inbound_lock, flags);
	stor_device->destroy = true;
	spin_unlock_irqrestore(&device->channel->inbound_lock, flags);


	storvsc_wait_to_drain(stor_device);


	spin_lock_irqsave(&device->channel->inbound_lock, flags);
	hv_set_drvdata(device, NULL);
	spin_unlock_irqrestore(&device->channel->inbound_lock, flags);


	vmbus_close(device->channel);

	kfree(stor_device->stor_chns);
	kfree(stor_device);
	return 0;
}
