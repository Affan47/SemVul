bfad_handle_qfull(struct bfad_itnim_s *itnim, struct scsi_device *sdev)
{
	struct scsi_device *tmp_sdev;

	itnim->last_queue_full_time = jiffies;

	shost_for_each_device(tmp_sdev, sdev->host) {
		if (tmp_sdev->id != sdev->id)
			continue;
		scsi_track_queue_full(tmp_sdev, tmp_sdev->queue_depth - 1);
	}
}
