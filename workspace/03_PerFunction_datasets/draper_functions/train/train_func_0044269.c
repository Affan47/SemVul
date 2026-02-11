adsi_end_download(struct ast_channel *chan)
{
	int bytes = 0;
	unsigned char buf[256];


	bytes += adsi_download_disconnect(buf + bytes);
	if (adsi_transmit_message_full(chan, buf, bytes, ADSI_MSG_DOWNLOAD, 0)) {
		return -1;
	}
	return 0;
}
