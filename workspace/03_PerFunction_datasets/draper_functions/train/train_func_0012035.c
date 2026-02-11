send_error(http_error_code_t e, bool kill_conn)
{
	string http_header = "HTTP/1.1 ";

	if (e >= HTTP_ERROR_END)
		e = HTTP_ERROR_400;
	http_header += http_error_msgs[e];
	http_header += "\r\nServer: lophttpd\r\nDate: ";
	http_header += gmt_date;

	if (e == HTTP_ERROR_405)
		http_header += "\r\nAllow: GET, HEAD, POST, PUT";

	http_header += "\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";

	if (writen(peer_idx, http_header.c_str(), http_header.size()) <= 0)
		return -1;

	if (kill_conn)
		shutdown(peer_idx);
	return 0;
}
