http_process_response(request_t *req, int r)
{
	req->len += r;
	if (!req->extracted) {
		if ((req->extracted =
		     extract_html(req->buffer, req->len))) {
			req->status_code = extract_status_code(req->buffer, req->len);
			r = req->len - (req->extracted - req->buffer);
			if (r) {
				memmove(req->buffer, req->extracted, r);
				MD5_Update(&req->context, req->buffer, r);
				r = 0;
			}
			req->len = r;
		}
	} else if (req->len) {
		MD5_Update(&req->context, req->buffer,
			   req->len);
		req->len = 0;
	}

	return 0;
}
