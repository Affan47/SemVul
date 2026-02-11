clientSetKeepaliveFlag(clientHttpRequest * http)
{
    request_t *request = http->request;
    const HttpHeader *req_hdr = &request->header;

    debug(33, 3) ("clientSetKeepaliveFlag: http_ver = %d.%d\n",
	request->http_ver.major, request->http_ver.minor);
    debug(33, 3) ("clientSetKeepaliveFlag: method = %s\n",
	request->method->string);
    {
	http_version_t http_ver;
	if (http->conn->port->http11)
	    http_ver = request->http_ver;
	else
	    httpBuildVersion(&http_ver, 1, 0);
	if (httpMsgIsPersistent(http_ver, req_hdr))
	    request->flags.proxy_keepalive = 1;
    }
}
