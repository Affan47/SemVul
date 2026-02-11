clientReplyBodyTooLarge(clientHttpRequest * http, squid_off_t clen)
{
    if (0 == http->maxBodySize)
	return 0;
    if (clen < 0)
	return 0;
    if (clen > http->maxBodySize)
	return 1;
    return 0;
}
