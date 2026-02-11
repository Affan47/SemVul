brasero_mmc1_read_toc_raw (BraseroDeviceHandle *handle,
			   int session_num,
			   BraseroScsiRawTocData **data,
			   int *size,
			   BraseroScsiErrCode *error)
{
	BraseroRdTocPmaAtipCDB *cdb;
	BraseroScsiResult res;

	g_return_val_if_fail (handle != NULL, BRASERO_SCSI_FAILURE);

	cdb = brasero_scsi_command_new (&info, handle);
	cdb->format = BRASERO_RD_TAP_RAW_TOC;


	cdb->track_session_num = session_num;

	res = brasero_read_toc_pma_atip (cdb,
					 sizeof (BraseroScsiRawTocDesc),
					(BraseroScsiTocPmaAtipHdr **) data,
					 size,
					 error);
	brasero_scsi_command_free (cdb);
	return res;
}
