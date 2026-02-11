smscore_register_device(struct smsdevice_params_t *params,
			    struct smscore_device_t **coredev,
			    void *mdev)
{
	struct smscore_device_t *dev;
	u8 *buffer;

	dev = kzalloc(sizeof(struct smscore_device_t), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	dev->media_dev = mdev;
#endif


	INIT_LIST_HEAD(&dev->entry);


	INIT_LIST_HEAD(&dev->clients);
	INIT_LIST_HEAD(&dev->buffers);


	spin_lock_init(&dev->clientslock);
	spin_lock_init(&dev->bufferslock);


	init_completion(&dev->version_ex_done);
	init_completion(&dev->data_download_done);
	init_completion(&dev->data_validity_done);
	init_completion(&dev->trigger_done);
	init_completion(&dev->init_device_done);
	init_completion(&dev->reload_start_done);
	init_completion(&dev->resume_done);
	init_completion(&dev->gpio_configuration_done);
	init_completion(&dev->gpio_set_level_done);
	init_completion(&dev->gpio_get_level_done);
	init_completion(&dev->ir_init_done);


	init_waitqueue_head(&dev->buffer_mng_waitq);


	dev->common_buffer_size = params->buffer_size * params->num_buffers;
	dev->common_buffer = dma_alloc_coherent(NULL, dev->common_buffer_size,
						&dev->common_buffer_phys,
						GFP_KERNEL | GFP_DMA);
	if (!dev->common_buffer) {
		smscore_unregister_device(dev);
		return -ENOMEM;
	}


	for (buffer = dev->common_buffer;
	     dev->num_buffers < params->num_buffers;
	     dev->num_buffers++, buffer += params->buffer_size) {
		struct smscore_buffer_t *cb;

		cb = smscore_createbuffer(buffer, dev->common_buffer,
					  dev->common_buffer_phys);
		if (!cb) {
			smscore_unregister_device(dev);
			return -ENOMEM;
		}

		smscore_putbuffer(dev, cb);
	}

	pr_debug("allocated %d buffers\n", dev->num_buffers);

	dev->mode = DEVICE_MODE_NONE;
	dev->board_id = SMS_BOARD_UNKNOWN;
	dev->context = params->context;
	dev->device = params->device;
	dev->setmode_handler = params->setmode_handler;
	dev->detectmode_handler = params->detectmode_handler;
	dev->sendrequest_handler = params->sendrequest_handler;
	dev->preload_handler = params->preload_handler;
	dev->postload_handler = params->postload_handler;

	dev->device_flags = params->flags;
	strcpy(dev->devpath, params->devpath);

	smscore_registry_settype(dev->devpath, params->device_type);


	kmutex_lock(&g_smscore_deviceslock);
	list_add(&dev->entry, &g_smscore_devices);
	kmutex_unlock(&g_smscore_deviceslock);

	*coredev = dev;

	pr_debug("device %p created\n", dev);

	return 0;
}
