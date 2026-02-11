ndmp_2to9_scsi_set_target_request (
  ndmp2_scsi_set_target_request *request2,
  ndmp9_scsi_set_target_request *request9)
{
	request9->device = NDMOS_API_STRDUP (request2->device.name);
	if (!request9->device) {
		return -1;
	}

	CNVT_TO_9 (request2, request9, target_controller);
	CNVT_TO_9 (request2, request9, target_id);
	CNVT_TO_9 (request2, request9, target_lun);

	return 0;
}
