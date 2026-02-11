era_destroy(struct era *era)
{
	if (era->md)
		metadata_close(era->md);

	if (era->wq)
		destroy_workqueue(era->wq);

	if (era->origin_dev)
		dm_put_device(era->ti, era->origin_dev);

	if (era->metadata_dev)
		dm_put_device(era->ti, era->metadata_dev);

	kfree(era);
}
