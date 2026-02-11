sub_client(__u32 client, char *path, size_t len)
{
	struct in_addr addr = { client };
	char buf[len];

	if (strstr(path, "%s") != NULL) {
		if (client == INADDR_NONE) {
			fprintf(stderr, "Root-NFS: no client address\n");
			exit(1);
		}

		snprintf(buf, len, path, inet_ntoa(addr));
		strcpy(path, buf);
	}

	return path;
}
