bs_sg_cmd_complete(int fd, int events, void *data)
{
	struct sg_io_hdr io_hdr;
	struct scsi_cmd *cmd;
	int err;
	unsigned resid;

	memset(&io_hdr, 0, sizeof(io_hdr));
	io_hdr.interface_id = 'S';
	io_hdr.pack_id = -1;

	err = graceful_read(fd, &io_hdr, sizeof(io_hdr));
	if (err)
		return;

	cmd = (struct scsi_cmd *)io_hdr.usr_ptr;
	if (!io_hdr.status) {
		scsi_set_out_resid(cmd, io_hdr.resid);
		scsi_set_in_resid(cmd, io_hdr.resid);
	} else {

		if (io_hdr.sbp[2] == 0x20)
			resid = io_hdr.dxfer_len - io_hdr.resid;
		else
			resid = 0;

		cmd->sense_len = io_hdr.sb_len_wr;
		scsi_set_out_resid_by_actual(cmd, resid);
		scsi_set_in_resid_by_actual(cmd, resid);
	}

	cmd->scsi_cmd_done(cmd, io_hdr.status);
}
