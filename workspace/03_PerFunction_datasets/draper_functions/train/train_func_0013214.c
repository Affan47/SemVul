callback_retr_status(struct PCP_retr *r,
				int status, void *vp)
{
	char status_buf[256];
	const char *comma="";

	status_buf[0]=0;

	if (status & LIST_CANCELLED)
	{
		strcat(strcat(status_buf, comma), "CANCELLED");
		comma=",";
	}

	if (status & LIST_BOOKED)
	{
		strcat(strcat(status_buf, comma), "BOOKED");
		comma=",";
	}

	if (status & LIST_PROXY)
	{
		strcat(strcat(status_buf, comma), "PROXY");
		comma=",";
	}
	if (status_buf[0])
		printf("110 %s %s\n", r->event_id, status_buf);
	return (0);
}
