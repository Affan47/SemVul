ir_raw_event_register(struct rc_dev *dev)
{
	int rc;
	struct ir_raw_handler *handler;

	if (!dev)
		return -EINVAL;

	dev->raw = kzalloc(sizeof(*dev->raw), GFP_KERNEL);
	if (!dev->raw)
		return -ENOMEM;

	dev->raw->dev = dev;
	dev->change_protocol = change_protocol;
	rc = kfifo_alloc(&dev->raw->kfifo,
			 sizeof(struct ir_raw_event) * MAX_IR_EVENT_SIZE,
			 GFP_KERNEL);
	if (rc < 0)
		goto out;

	spin_lock_init(&dev->raw->lock);
	dev->raw->thread = kthread_run(ir_raw_event_thread, dev->raw,
				       "rc%u", dev->minor);

	if (IS_ERR(dev->raw->thread)) {
		rc = PTR_ERR(dev->raw->thread);
		goto out;
	}

	mutex_lock(&ir_raw_handler_lock);
	list_add_tail(&dev->raw->list, &ir_raw_client_list);
	list_for_each_entry(handler, &ir_raw_handler_list, list)
		if (handler->raw_register)
			handler->raw_register(dev);
	mutex_unlock(&ir_raw_handler_lock);

	return 0;

out:
	kfree(dev->raw);
	dev->raw = NULL;
	return rc;
}
