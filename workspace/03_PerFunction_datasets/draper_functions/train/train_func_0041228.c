get_sock_family_from_val(int val)
{
	int i;

	for (i = 0; i < SIZE(sock_families); i++) {
		if (sock_families[i].family_val == val)
			return sock_families[i].family_name;
	}

	fprintf(stderr, "Invalid socket family detected.\n");
	exit(EXIT_FAILURE);

	return NULL;
}
