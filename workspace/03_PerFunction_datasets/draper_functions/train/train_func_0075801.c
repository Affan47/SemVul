make_http_request_text(char * host, int port, char * path,
		       int use_proxy, char * proxy,
		       long long start_byte, char * msg, int msg_len) {

	char extra_header[1024];

	if (start_byte != 0) {
		snprintf(extra_header, sizeof(extra_header), "Range: bytes=%lld-\r\n", start_byte);
	} else {
		extra_header[0] = '\0';
	}

	if (!use_proxy) {
		if (port == 80) {
			snprintf(msg, msg_len,
				 "GET %s HTTP/1.1\r\n"
				 "Host: %s\r\n"
				 "User-Agent: Aqualung/%s\r\n"
				 "icy-metadata: 1\r\n"
				 "%s"
				 "Connection: close\r\n\r\n",
				 path, host, AQUALUNG_VERSION, extra_header);
		} else {
			snprintf(msg, msg_len,
				 "GET %s HTTP/1.1\r\n"
				 "Host: %s:%d\r\n"
				 "User-Agent: Aqualung/%s\r\n"
				 "icy-metadata: 1\r\n"
				 "%s"
				 "Connection: close\r\n\r\n",
				 path, host, port, AQUALUNG_VERSION, extra_header);
		}
	} else {
		if (port == 80) {
			snprintf(msg, msg_len,
				 "GET http://%s%s HTTP/1.1\r\n"
				 "Host: %s\r\n"
				 "User-Agent: Aqualung/%s\r\n"
				 "icy-metadata: 1\r\n"
				 "%s"
				 "Connection: close\r\n\r\n",
				 host, path, host, AQUALUNG_VERSION, extra_header);
		} else {
			snprintf(msg, msg_len,
				 "GET http://%s:%d%s HTTP/1.1\r\n"
				 "Host: %s:%d\r\n"
				 "User-Agent: Aqualung/%s\r\n"
				 "icy-metadata: 1\r\n"
				 "%s"
				 "Connection: close\r\n\r\n",
				 host, port, path, host, port, AQUALUNG_VERSION, extra_header);
		}
	}
}
