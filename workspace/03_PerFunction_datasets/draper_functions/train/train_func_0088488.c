get_path_dst_uri(str *_p, str *_dst)
{
	rr_t *route = 0;

	LM_DBG("path for branch: '%.*s'\n",	_p->len, _p->s);

	if(parse_rr_body(_p->s, _p->len, &route) < 0) {
		LM_ERR("failed to parse Path body\n");
		return -1;
	}
	if(!route) {
		LM_ERR("failed to parse Path body no head found\n");
		return -1;
	}

	*_dst = route->nameaddr.uri;
	free_rr(&route);

	return 0;
}
