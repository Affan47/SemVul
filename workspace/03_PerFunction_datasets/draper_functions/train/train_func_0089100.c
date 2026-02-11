mkredirect(struct REQUEST *req)
{
    req->status = 302;
    req->body   = req->path;
    req->lbody  = strlen(req->body);
    req->lres = sprintf(req->hres,
			RESPONSE_START
			"Location: http://%s:%d%s\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: %d\r\n",
			"302 Redirect",server_name,
			req->keep_alive ? "Keep-Alive" : "Close",
			req->hostname,tcp_port,req->path,
			req->lbody);
    req->lres += strftime(req->hres+req->lres,80,
			  "Date: " RFCTIME "\r\n\r\n",
			  gmtime(&now));
    req->state = STATE_WRITE_HEADER;
    if (debug)
	fprintf(stderr,"%03d: 302 redirect: %s, connection=%s\n",
		req->fd, req->path, req->keep_alive ? "Keep-Alive" : "Close");
}
