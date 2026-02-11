is_queued_reconnect(unsigned char *buf, int len, int *conn)
{
    int ptr = sizeof(LAT_SessionCmd)+3;

    ptr += buf[ptr]+1;
    if (ptr >= len) return false;

    ptr += buf[ptr]+1;
    if (ptr >= len) return false;


    while (ptr < len)
    {
	int param_type = buf[ptr++];
	if (param_type == 2)
	{
	    ptr++;
	    unsigned short param = dn_ntohs(*(unsigned short *)(buf+ptr));

	    debuglog(("found Parameter 2: request ID is %d\n", param));
	    *conn = param;
	    ptr +=2;
	    return true;
	}
	else
	{
	    ptr += buf[ptr]+1;
	}
    }
    return false;
}
