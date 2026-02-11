get_nats(void)
{
  char *http_cookie, *p, *r, *s;
  Dsvec *nats;
  Nat *nat;

  nats = NULL;
  if ((http_cookie = getenv("HTTP_COOKIE")) == NULL || *http_cookie == '\0') {
	log_msg((LOG_TRACE_LEVEL, "HTTP_COOKIE is NULL"));
	if ((http_cookie = non_auth_cookie_header) == NULL) {
	  log_msg((LOG_TRACE_LEVEL, "No NAT cookie found"));
	  return(NULL);
	}
	log_msg((LOG_TRACE_LEVEL, "Using non_auth_cookie_header..."));
  }
  else
	log_msg((LOG_TRACE_LEVEL, "Using HTTP_COOKIE..."));

  p = s = strdup(http_cookie);
  while (p != NULL) {


	if ((r = strchr(p, (int) ';')) != NULL) {
	  *r++ = '\0';
	  while (*r == ' ')
		r++;
	}
	else if ((r = strchr(p, (int) ',')) != NULL) {
	  *r++ = '\0';
	  while (*r == ' ')
		r++;
	}

	s = p;
	p = r;


	if ((nat = parse_nat_cookie(s)) != NULL) {
	  if (nats == NULL)
		nats = dsvec_init(NULL, sizeof(Nat *));
	  dsvec_add_ptr(nats, nat);
	  log_msg((LOG_TRACE_LEVEL, "Accepting NAT: %s", nat_show(nat)));
	}
	else
	  log_msg((LOG_TRACE_LEVEL, "Ignoring non-NAT cookie: \"%s\"", s));
  }

  return(nats);
}
