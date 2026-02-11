httpRequestPackDebug(request_t * req, Packer * p)
{
    assert(req && p);

    packerPrintf(p, "Client: %s ", inet_ntoa(req->client_addr));
    packerPrintf(p, "http_port: %s:%d", inet_ntoa(req->my_addr), req->my_port);
    if (req->auth_user_request && authenticateUserRequestUsername(req->auth_user_request))
	packerPrintf(p, "user: %s", authenticateUserRequestUsername(req->auth_user_request));
    packerPrintf(p, "\n");

    packerPrintf(p, "%s %s HTTP/%d.%d\r\n",
	req->method->string, urlCanonical(req), req->http_ver.major, req->http_ver.minor);

    httpHeaderPackInto(&req->header, p);

    packerAppend(p, "\r\n", 2);
}
