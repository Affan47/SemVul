scsi_dh_set_params(struct request_queue *q, const char *params)
{
	struct scsi_device *sdev;
	int err = -SCSI_DH_NOSYS;

	sdev = scsi_device_from_queue(q);
	if (!sdev)
		return err;

	if (sdev->handler && sdev->handler->set_params)
		err = sdev->handler->set_params(sdev, params);
	put_device(&sdev->sdev_gendev);
	return err;
}
