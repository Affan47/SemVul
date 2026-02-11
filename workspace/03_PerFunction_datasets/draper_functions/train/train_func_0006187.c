w_lookup_netname_other(char *addr, char *serv)
{
	token_t *ls;
	ip_blk_t *a = NULL, *b = NULL;
	char *reply, *ans = NULL;
	int i;
	int use_this = 1;

	if (!addr || !serv)
		return NULL;

	reply = w_ask(serv, addr);
	if (!reply)
		return NULL;
	ls = tokens(reply, "\n");

	for (i = 0; ls[i].ptr; i++) {
		char *value;
		if ((value = match_prefix("inetnum:", ls[i].ptr))) {
			a = match_ipprefix(value);

			if (b) {
				if (((b->end - b->start) > (a->end - a->start))) {
					use_this = 1;
					free(b);
					b = a;
					a = NULL;
				} else {
					use_this = 0;
					free(a);
					a = NULL;
				}
			} else {
				use_this = 1;
				b = a;
				a = NULL;
			}
		}
		if (use_this && (value = match_prefix("netname:", ls[i].ptr))) {
			if (ans)
				free(ans);
			ans = value;
		}
	}

	free(ls); free(reply); if (b) free(b);
	return ans;
}
