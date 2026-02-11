parse_http_url(struct whpl_conn* conn, char** buf, size_t* n)
{
	struct http_parser* hp = &conn->hp;
	struct whpl_req* req = &conn->req;
	if (hp->begin == 0) hp->begin = *buf;
	while ((*n) > 0) {
		char c = **buf;
		if (c == ' ') {
			size_t len = *buf - hp->begin;
			req->raw_url = abuffer_alloc(conn->perm_buffer, len + 1);
			if (req->raw_url == NULL) {
				errf("eeek! out of perm_buffer memory when trying to allocate %zu for url", len + 1);
				drop_conn(conn);
				return;
			}
			memcpy(req->raw_url, hp->begin, len);
			req->raw_url[len] = 0;
			dbgf("got url: %s", req->raw_url);
			req->path = req->raw_url;
			req->subpath = req->path;


			(*buf)++;
			(*n)--;
			hp->where = HP_VERSION;
			hp->begin = 0;
			return;
		}
		(*buf)++;
		(*n)--;
	}
}
