handle_read_request(struct tftp_request *req_p)
{
	int ret;

	ret = tftp_service_send_data(req_p->filename, req_p->offset, req_p->size, req_p->file_mode, &req_p->client_addr);
	if (ret < 0)
	{
		println("Send file \"%s\" failed", req_p->filename);
	}
	else
	{
		println("Send file \"%s\" success", req_p->filename);
	}

	return ret;
}
