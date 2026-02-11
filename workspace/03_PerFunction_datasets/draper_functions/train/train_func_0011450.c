spc_pr_report_capabilities(int host_no, struct scsi_cmd *cmd)
{
	uint16_t asc = ASC_INVALID_FIELD_IN_CDB;
	uint8_t key = ILLEGAL_REQUEST;
	uint8_t *buf;
	uint16_t len;

	len = get_unaligned_be16(cmd->scb + 7);
	if (len < 8)
		goto sense;

	if (scsi_get_in_length(cmd) < len)
		goto sense;

	buf = scsi_get_in_buffer(cmd);

	len = 8;

	memset(buf, 0, len);

	put_unaligned_be16(len, &buf[0]);


	buf[4] |= 0x80;
	buf[4] |= 0x40;
	buf[4] |= 0x20;
	buf[4] |= 0x08;
	buf[4] |= 0x02;
	buf[5] |= 0x01;

	return SAM_STAT_GOOD;
sense:
	scsi_set_in_resid_by_actual(cmd, 0);
	sense_data_build(cmd, key, asc);
	return SAM_STAT_CHECK_CONDITION;
}
