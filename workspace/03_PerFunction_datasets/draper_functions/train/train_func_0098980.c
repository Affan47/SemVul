tcp_dd_handle_write_request(struct network_client *client, struct tcp_dd_file_request *req)
{
	int fd;
	int ret;
	mode_t mode;

	mode = file_get_mode(req->filename);
	switch (mode & S_IFMT)
	{
	case S_IFREG:
		pr_info("remove regular file %s", req->filename);
		unlink(req->filename);
		break;

	case S_IFBLK:
		pr_info("umount block device %s", req->filename);
		umount_device(req->filename, MNT_DETACH);
		break;
	}

	fd = open(req->filename, O_CREAT | O_WRONLY | O_TRUNC | O_BINARY, req->mode);
	if (fd < 0)
	{

		tcp_dd_send_response(client, fd, "[Server] Open file `%s' failed", req->filename);
		return fd;
	}

	ret = lseek(fd, req->offset, SEEK_SET);
	if (ret < 0)
	{
		tcp_dd_send_response(client, ret, "[Server] Seek file failed");
		goto out_close_fd;
	}

	ret = tcp_dd_send_response(client, 0, "[Server] Start receive file");
	if (ret < 0)
	{
		pr_red_info("tcp_dd_send_response");
		return ret;
	}

	println("filename = %s", req->filename);
	println("offset = %s", size2text(req->offset));
	println("size = %s", size2text(req->size));

	ret = network_client_recv_file(client, fd, req->size);

out_close_fd:
	close(fd);

	return ret;
}
