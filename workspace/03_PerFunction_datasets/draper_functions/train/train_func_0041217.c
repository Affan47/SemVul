scsi_target_reap_ref_release(struct kref *kref)
{
	struct scsi_target *starget
		= container_of(kref, struct scsi_target, reap_ref);


	if (starget->state != STARGET_CREATED) {
		transport_remove_device(&starget->dev);
		device_del(&starget->dev);
	}
	scsi_target_destroy(starget);
}
