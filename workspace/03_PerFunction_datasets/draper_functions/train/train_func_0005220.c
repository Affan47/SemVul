xillybus_init_endpoint(struct pci_dev *pdev,
					      struct device *dev,
					      struct xilly_endpoint_hardware
					      *ephw)
{
	struct xilly_endpoint *endpoint;

	endpoint = devm_kzalloc(dev, sizeof(*endpoint), GFP_KERNEL);
	if (!endpoint)
		return NULL;

	endpoint->pdev = pdev;
	endpoint->dev = dev;
	endpoint->ephw = ephw;
	endpoint->msg_counter = 0x0b;
	endpoint->failed_messages = 0;
	endpoint->fatal_error = 0;

	init_waitqueue_head(&endpoint->ep_wait);
	mutex_init(&endpoint->register_mutex);

	return endpoint;
}
