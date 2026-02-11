kmc_get_display_size(int fd, char *displaysize)
{
	char mode_wbuff[1], out;

	mode_wbuff[0] = '\x8A';
	out = kmc_wr(fd, mode_wbuff);

	if(out == '\x00') sprintf(displaysize,"128x40");
	if(out == '\x01') sprintf(displaysize,"128x80");
	if(out == '\x02') sprintf(displaysize,"128x120");
	if(out == '\x03') sprintf(displaysize,"256x120");
	if(out == '\x04') sprintf(displaysize,"256x240");
	if(out == '\x05') sprintf(displaysize,"512x240");
	if(out == '\x06') sprintf(displaysize,"512x480");

}
