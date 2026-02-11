http_wait_response(Http *h)
{
  int rc, sock;

  sock = (h->ssl_args != NULL) ? h->ssl_read_fd : h->sd;


  log_msg((LOG_TRACE_LEVEL, "Closing output stream..."));
  if (h->ssl_args != NULL) {
	close(h->ssl_write_fd);
	h->ssl_write_fd = -1;
	log_msg((LOG_TRACE_LEVEL, "SSL pipe closed"));
  }
  else {


	struct timeval timeout;

	timeout.tv_sec = 4;
	timeout.tv_usec = 0;
	if (net_input_or_timeout(h->sd, &timeout) != 1)
	  shutdown(h->sd, SHUT_WR);
  }

  h->in_data = 0;

  log_msg((LOG_TRACE_LEVEL, "Reading response..."));

  rc = parse_response(h);

  return(rc);
}
