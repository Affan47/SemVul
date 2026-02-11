afp_write(struct afp_volume * volume, unsigned short forkid,
	uint32_t offset, uint32_t reqcount,
	char * data,uint32_t * written)
{
	struct {
		struct dsi_header dsi_header __attribute__((__packed__));
		uint8_t command;
		uint8_t flag;
		uint16_t forkid;
		uint32_t offset;
		uint32_t reqcount;
	}  __attribute__((__packed__)) * request_packet;
	struct afp_server * server = volume->server;

	unsigned int len = sizeof(*request_packet)+
		reqcount;
	int ret;
	char * dataptr, * msg;

	if ((msg = malloc(len))==NULL)
		return -1;

	request_packet =(void *) msg;
	dataptr=msg+(sizeof(*request_packet));
	memcpy(dataptr,data,reqcount);
	dsi_setup_header(server,&request_packet->dsi_header,DSI_DSIWrite);
	request_packet->dsi_header.return_code.data_offset=htonl(sizeof(*request_packet)-sizeof(struct dsi_header));

	request_packet->command=afpWrite;
	request_packet->flag=0;
	request_packet->forkid=htons(forkid);
	request_packet->offset=htonl(offset);
	request_packet->reqcount=htonl(reqcount);
	ret=dsi_send(server, (char *) request_packet,len,DSI_DEFAULT_TIMEOUT,
		afpWrite,(void *) written);

	free(msg);

	return ret;
}
