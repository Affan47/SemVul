send_http_header()
{
	int l = 0;


	if (cur_range_requested) {
		l = snprintf(hbuf, sizeof(hbuf), part_hdr_fmt.c_str(),
	                     gmt_date, peer->left, misc::content_types[peer->ct].c_type.c_str(),
			     cur_start_range, cur_end_range - 1, cur_stat.st_size);

	} else if (peer->ftype == FILE_PROC) {
		l = snprintf(hbuf, sizeof(hbuf), chunked_hdr_fmt.c_str(),
		             gmt_date, "text/plain");
	} else {
		l = snprintf(hbuf, sizeof(hbuf), hdr_fmt.c_str(),
	                     gmt_date, peer->left, misc::content_types[peer->ct].c_type.c_str());
	}

	if (l < 0 || l > (int)sizeof(hbuf))
		return -1;

	int r = peer->send(hbuf, l);

	if (r != l)
		return -1;

	return r;
}
