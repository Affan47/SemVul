afp_getfiledirparms_reply(struct afp_server *server, char * buf, unsigned int size,
	void * other)
{
	struct {
		struct dsi_header header __attribute__((__packed__));
		uint16_t filebitmap;
		uint16_t dirbitmap;
		uint8_t isdir;
		uint8_t pad;
	}  __attribute__((__packed__)) * reply_packet = (void *) buf;
	struct afp_file_info * filecur = other;

	if  (reply_packet->header.return_code.error_code)
		return reply_packet->header.return_code.error_code;

	if (size<sizeof(*reply_packet))
		return -1;

	parse_reply_block(server,
		buf + (sizeof(*reply_packet)),
		size,
		reply_packet->isdir,
		ntohs(reply_packet->filebitmap),
		ntohs(reply_packet->dirbitmap),
		filecur);
	filecur->isdir=reply_packet->isdir;

	return 0;
}
