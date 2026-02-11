rnc_destruct_done(void *_dev)
{
	struct isci_remote_device *idev = _dev;

	BUG_ON(idev->started_request_count != 0);
	sci_change_state(&idev->sm, SCI_DEV_STOPPED);
}
