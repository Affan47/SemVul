check_mask(SERVER_REC *server, const char *mask,
		      const char *str, int wildcards)
{
	if (server != NULL && server->mask_match_func != NULL) {

		return server->mask_match_func(mask, str);
	}

	return wildcards ? match_wildcards(mask, str) :
		g_strcasecmp(mask, str) == 0;
}
