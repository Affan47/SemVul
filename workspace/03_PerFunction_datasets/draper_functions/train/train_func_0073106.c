DCC_write_nolog(dccrec *d, char *format, ...)


{
	va_list va;
	int bytes;


	if(d == NULL)
		return;


	DCC->send_buf1[0] = 0;
	va_start(va,format);
	vsprintf(DCC->send_buf1,format,va);
	va_end(va);

	if(d->flags & (CLIENT_IRC_CHAT|CLIENT_SMTP|STAT_GATEWAYCLIENT))
		strcat(DCC->send_buf1,"\n");
	else
		strcat(DCC->send_buf1,"\r\n");


	if(d->socket < 0)
		return;


	bytes = strlen(DCC->send_buf1);
	d->bytes_out += bytes;


	DCC->bytes_out += bytes;

	net_sockputs(d->socket, DCC->send_buf1, bytes);
}
