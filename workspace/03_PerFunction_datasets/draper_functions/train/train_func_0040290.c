cxgb3i_dev_event_handler(struct t3cdev *t3dev, u32 event, u32 port)
{
	struct cxgbi_device *cdev = cxgbi_device_find_by_lldev(t3dev);

	log_debug(1 << CXGBI_DBG_TOE,
		"0x%p, cdev 0x%p, event 0x%x, port 0x%x.\n",
		t3dev, cdev, event, port);
	if (!cdev)
		return;

	switch (event) {
	case OFFLOAD_STATUS_DOWN:
		cdev->flags |= CXGBI_FLAG_ADAPTER_RESET;
		break;
	case OFFLOAD_STATUS_UP:
		cdev->flags &= ~CXGBI_FLAG_ADAPTER_RESET;
		break;
	}
}
