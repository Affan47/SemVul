find_match(gfx_res_conf_t *conflist,
	   int type, int nr, int loop, int cel)
{
	while (conflist) {
		if (resource_matches_patternlists(conflist,
						  type, nr, loop, cel)) {
#ifdef DEBUG
			fprintf(stderr, "[DEBUG:gfx-res] Found match!\n");
#endif
			return conflist;
		}

		conflist = conflist->next;
	}
	return NULL;
}
