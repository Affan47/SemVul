handle_retr(void)
{
	struct stat statbuf;
	off_t bytes_transferred;
	int remote_fd;
	int local_file_fd;
	off_t offset = G.restart_pos;
	char *response;

	G.restart_pos = 0;

	if (!port_or_pasv_was_seen())
		return;


	local_file_fd = G.ftp_arg ? open(G.ftp_arg, O_RDONLY | O_NONBLOCK) : -1;
	if (local_file_fd < 0) {
		WRITE_ERR(FTP_FILEFAIL);
		return;
	}

	if (fstat(local_file_fd, &statbuf) != 0 || !S_ISREG(statbuf.st_mode)) {

		WRITE_ERR(FTP_FILEFAIL);
		goto file_close_out;
	}
	G.local_file_fd = local_file_fd;


	ndelay_off(local_file_fd);


	if (offset != 0)
		xlseek(local_file_fd, offset, SEEK_SET);

	response = xasprintf(
		" Opening BINARY connection for %s (%"OFF_FMT"u bytes)",
		G.ftp_arg, statbuf.st_size);
	remote_fd = get_remote_transfer_fd(response);
	free(response);
	if (remote_fd < 0)
		goto file_close_out;

	bytes_transferred = bb_copyfd_eof(local_file_fd, remote_fd);
	close(remote_fd);
	if (bytes_transferred < 0)
		WRITE_ERR(FTP_BADSENDFILE);
	else
		WRITE_OK(FTP_TRANSFEROK);

 file_close_out:
	close(local_file_fd);
	G.local_file_fd = 0;
}
