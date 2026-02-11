rdac_bus_detach( struct scsi_device *sdev )
{
	struct rdac_dh_data *h = sdev->handler_data;

	if (h->ctlr && h->ctlr->ms_queued)
		flush_workqueue(kmpath_rdacd);

	spin_lock(&list_lock);
	if (h->ctlr)
		kref_put(&h->ctlr->kref, release_controller);
	spin_unlock(&list_lock);
	sdev->handler_data = NULL;
	kfree(h);
}
