http_parse_command_url(struct http_connection *hc, struct evbuffer *input) {
	char	*p=(char *) EVBUFFER_DATA(input);
	char	*elem[10];
	int	no;

	no=split_string_by_space(p, elem, 10);


	if (no != 3)
		return 0;

	if ((hc->cmd=http_get_cmd(elem[0])) == HC_CMD_UNKNOWN)
		return 0;

	hc->url=strdup(elem[1]);
	hc->proto=http_parse_proto(elem[2]);

	if (hc->proto == HP_HTTP11)
		hc->keepalive=1;
	else
		hc->keepalive=0;

	return 1;
}
