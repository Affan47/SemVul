write_link_key(bdaddr_t *local, bdaddr_t *peer, unsigned char *key, uint8_t type, int length)
{
	char filename[PATH_MAX + 1], addr[18], str[38];
	int i;

	memset(str, 0, sizeof(str));
	for (i = 0; i < 16; i++)
		sprintf(str + (i * 2), "%2.2X", key[i]);
	sprintf(str + 32, " %d %d", type, length);

	create_filename(filename, PATH_MAX, local, "linkkeys");

	create_file(filename, S_IRUSR | S_IWUSR);

	ba2str(peer, addr);

	if (length < 0) {
		char *tmp = textfile_get(filename, addr);
		if (tmp) {
			if (strlen(tmp) > 34)
				memcpy(str + 34, tmp + 34, 3);
			free(tmp);
		}
	}

	return textfile_put(filename, addr, str);
}
