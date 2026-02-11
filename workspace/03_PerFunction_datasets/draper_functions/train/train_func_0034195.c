get_server_uh(struct proxy *px, char *uri, int uri_len)
{
	unsigned long hash = 0;
	int c;
	int slashes = 0;

	if (px->lbprm.tot_weight == 0)
		return NULL;


	if (px->lbprm.tot_used == 1)
		goto hash_done;

	if (px->uri_len_limit)
		uri_len = MIN(uri_len, px->uri_len_limit);

	while (uri_len--) {
		c = *uri++;
		if (c == '/') {
			slashes++;
			if (slashes == px->uri_dirs_depth1)
				break;
		}
		else if (c == '?' && !px->uri_whole)
			break;

		hash = c + (hash << 6) + (hash << 16) - hash;
	}
 hash_done:
	if (px->lbprm.algo & BE_LB_LKUP_CHTREE)
		return chash_get_server_hash(px, hash);
	else
		return map_get_server_hash(px, hash);
}
