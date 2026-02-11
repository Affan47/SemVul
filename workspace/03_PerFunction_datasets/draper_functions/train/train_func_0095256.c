istgt_lu_tape_read_media_check(ISTGT_LU_TAPE *spec, CONN_Ptr conn, ISTGT_LU_CMD_Ptr lu_cmd, uint64_t request_len)
{
	uint64_t tape_leader;
	uint64_t mediasize;
	uint64_t offset;
	int data_len;

	tape_leader = spec->ctlblock->ctlblocklen;
	mediasize = spec->size;
	offset = spec->offset;


	if (mediasize < tape_leader) {

		data_len
			= istgt_lu_tape_build_sense_data(spec, lu_cmd->sense_data,
											 ISTGT_SCSI_SENSE_HARDWARE_ERROR,
											 0x44, 0x00);
		lu_cmd->sense_data_len = data_len;
		lu_cmd->status = ISTGT_SCSI_STATUS_CHECK_CONDITION;
		return -1;
	}
	mediasize -= tape_leader;


	if (request_len > mediasize || offset > mediasize - request_len) {

		spec->eom = 1;

		data_len
			= istgt_lu_tape_build_sense_data(spec, lu_cmd->sense_data,
											 ISTGT_SCSI_SENSE_MEDIUM_ERROR,
											 0x00, 0x02);
		lu_cmd->sense_data_len = data_len;
		lu_cmd->status = ISTGT_SCSI_STATUS_CHECK_CONDITION;
		return -1;
	}


	return 0;
}
