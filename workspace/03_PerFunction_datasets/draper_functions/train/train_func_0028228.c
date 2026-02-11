free_host(struct hostent *ho) {
	char **p;

	if (ho == NULL) {
		return;
	}

	if (ho->h_name != NULL)
		free(ho->h_name);

	if (ho->h_aliases != NULL) {
		for (p = ho->h_aliases ; *p != NULL ; p++)
			free(*p);
		free(ho->h_aliases);
	}

	if (ho->h_addr_list != NULL) {
		for (p = ho->h_addr_list ; *p != NULL ; p++)
			free(*p);
		free(ho->h_addr_list);
	}
}
