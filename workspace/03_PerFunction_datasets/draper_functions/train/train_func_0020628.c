afp_createdir(struct afp_volume * volume, unsigned int dirid, const char * pathname, unsigned int *did_p)
{
	struct {
		struct dsi_header dsi_header __attribute__((__packed__));
		uint8_t command;
		uint8_t pad;
		uint16_t volid;
		uint32_t dirid;
	} __attribute__((__packed__)) * request_packet;
	char * pathptr;
	char * msg;
	struct afp_server * server = volume->server;
	unsigned int len = sizeof(*request_packet) +
                sizeof_path_header(server) + strlen(pathname);
	int ret;

        if ((msg=malloc(len)) == NULL)
                return -1;

        pathptr=msg+sizeof(*request_packet);
        request_packet = (void *) msg;

	dsi_setup_header(server,&request_packet->dsi_header,DSI_DSICommand);

	request_packet->command=afpCreateDir;
	request_packet->pad=0;
	request_packet->volid=htons(volume->volid);
	request_packet->dirid=htonl(dirid);

	copy_path(server,pathptr,pathname,strlen(pathname));
	unixpath_to_afppath(server,pathptr);

	ret=dsi_send(server, (char *) msg,len,DSI_DEFAULT_TIMEOUT,
		afpCreateDir,(void *)did_p);
	free(msg);
	return ret;

}
