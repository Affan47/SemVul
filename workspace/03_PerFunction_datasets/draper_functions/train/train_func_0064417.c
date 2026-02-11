nvme_trans_write_buffer(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = 0;
	u32 buffer_offset, parm_list_length;
	u8 buffer_id, mode;

	parm_list_length = get_unaligned_be24(&cmd[6]);
	if (parm_list_length % BYTES_TO_DWORDS != 0) {

		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}
	buffer_id = cmd[2];
	if (buffer_id > NVME_MAX_FIRMWARE_SLOT) {
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	}
	mode = cmd[1] & 0x1f;
	buffer_offset = get_unaligned_be24(&cmd[3]);

	switch (mode) {
	case DOWNLOAD_SAVE_ACTIVATE:
		res = nvme_trans_send_download_fw_cmd(ns, hdr, nvme_admin_download_fw,
						parm_list_length, buffer_offset,
						buffer_id);
		if (res)
			goto out;
		res = nvme_trans_send_activate_fw_cmd(ns, hdr, buffer_id);
		break;
	case DOWNLOAD_SAVE_DEFER_ACTIVATE:
		res = nvme_trans_send_download_fw_cmd(ns, hdr, nvme_admin_download_fw,
						parm_list_length, buffer_offset,
						buffer_id);
		break;
	case ACTIVATE_DEFERRED_MICROCODE:
		res = nvme_trans_send_activate_fw_cmd(ns, hdr, buffer_id);
		break;
	default:
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		break;
	}

 out:
	return res;
}
