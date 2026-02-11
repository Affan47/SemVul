write()
{
    int er;

    if (outbuf[last_msg_start+1] & 0x02)
    {

	if (outbuf[last_msg_start+1] & 0x04)
        {
		unsigned short len = dn_htons(outbufptr - last_msg_start - 4);
		memcpy(&outbuf[last_msg_start+2], &len, sizeof(unsigned short));
	}
	else
        {
	    outbuf[last_msg_start+2] = outbufptr - last_msg_start - 3;
        }
    }


    if (blocked && (outbufptr < blocksize))
    {
	last_msg_start = outbufptr;
	return true;
    }


    if (blocked && (outbufptr >= blocksize))
    {
	if (verbose > 2)
  	    DAPLOG((LOG_INFO, "block is over-full(%d), Sending %d bytes\n",
		    outbufptr, last_msg_start));

	er=::write(sockfd,outbuf,last_msg_start);
	if (er < 0)
	{
	    if (errno == ENOTCONN)
		sprintf(errstring, "write failed: %s", connerror(strerror(errno)));
	    else
		sprintf(errstring, "DAP write error: %s", strerror(errno));
	    lasterror = errstring;
	    return false;
	}


	memmove(outbuf, outbuf+last_msg_start, outbufptr - last_msg_start);
	outbufptr -= last_msg_start;
	last_msg_start = outbufptr;

	if (verbose > 2)
	    DAPLOG((LOG_INFO, "Wrote %d bytes, buffer size is now %d bytes\n",
		    er, outbufptr));
	return true;
    }


    er=::write(sockfd,outbuf,outbufptr);
    if (er < 0)
    {
	if (errno == ENOTCONN)
	    sprintf(errstring, "write failed: %s", connerror(strerror(errno)));
	else
	    sprintf(errstring, "DAP write error: %s", strerror(errno));
	lasterror = errstring;
	return false;
    }
    if (verbose > 2) DAPLOG((LOG_DEBUG, "wrote %d bytes\n", er));

    outbufptr = last_msg_start = 0;

    return true;
}
