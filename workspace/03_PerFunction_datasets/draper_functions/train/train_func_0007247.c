sd_try_extended_inquiry(struct scsi_device *sdp)
{


	if (sdp->try_vpd_pages)
		return 1;


	if (sdp->scsi_level > SCSI_SPC_2 && !sdp->skip_vpd_pages)
		return 1;
	return 0;
}
