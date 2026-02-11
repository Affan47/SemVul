smscore_unregister_device(struct smscore_device_t *coredev)
{
	struct smscore_buffer_t *cb;
	int num_buffers = 0;
	int retry = 0;

	kmutex_lock(&g_smscore_deviceslock);


	sms_ir_exit(coredev);

	smscore_notify_clients(coredev);
	smscore_notify_callbacks(coredev, NULL, 0);


	while (1) {
		while (!list_empty(&coredev->buffers)) {
			cb = (struct smscore_buffer_t *) coredev->buffers.next;
			list_del(&cb->entry);
			kfree(cb);
			num_buffers++;
		}
		if (num_buffers == coredev->num_buffers)
			break;
		if (++retry > 10) {
			pr_info("exiting although not all buffers released.\n");
			break;
		}

		pr_debug("waiting for %d buffer(s)\n",
			 coredev->num_buffers - num_buffers);
		kmutex_unlock(&g_smscore_deviceslock);
		msleep(100);
		kmutex_lock(&g_smscore_deviceslock);
	}

	pr_debug("freed %d buffers\n", num_buffers);

	if (coredev->common_buffer)
		dma_free_coherent(NULL, coredev->common_buffer_size,
			coredev->common_buffer, coredev->common_buffer_phys);

	kfree(coredev->fw_buf);

	list_del(&coredev->entry);
	kfree(coredev);

	kmutex_unlock(&g_smscore_deviceslock);

	pr_debug("device %p destroyed\n", coredev);
}
