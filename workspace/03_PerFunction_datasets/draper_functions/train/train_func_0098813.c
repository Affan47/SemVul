scsi_prep_state_check(struct scsi_device *sdev, struct request *req)
{
	int ret = BLKPREP_OK;


	if (unlikely(sdev->sdev_state != SDEV_RUNNING)) {
		switch (sdev->sdev_state) {
		case SDEV_OFFLINE:
		case SDEV_TRANSPORT_OFFLINE:


			sdev_printk(KERN_ERR, sdev,
				    "rejecting I/O to offline device\n");
			ret = BLKPREP_KILL;
			break;
		case SDEV_DEL:


			sdev_printk(KERN_ERR, sdev,
				    "rejecting I/O to dead device\n");
			ret = BLKPREP_KILL;
			break;
		case SDEV_BLOCK:
		case SDEV_CREATED_BLOCK:
			ret = BLKPREP_DEFER;
			break;
		case SDEV_QUIESCE:


			if (!(req->cmd_flags & REQ_PREEMPT))
				ret = BLKPREP_DEFER;
			break;
		default:


			if (!(req->cmd_flags & REQ_PREEMPT))
				ret = BLKPREP_KILL;
			break;
		}
	}
	return ret;
}
