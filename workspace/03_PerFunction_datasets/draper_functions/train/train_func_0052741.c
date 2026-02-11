create_md5sum(const gchar* file, const gchar* md5_file) {
	int fd;
	gchar* text = NULL;
	gchar* md5sum = malloc(33);

	debug_print("Creating md5sum file: %s\n", md5_file);
	if (md5_hex_digest_file(md5sum, (const unsigned char *) file) == -1)
		return;
	debug_print("md5sum: %s\n", md5sum);
	if ((fd =
		open(md5_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
		return;
	text = g_strrstr_len(file, strlen(file), "/");
	if (text) {
		text++;
		text = g_strdup_printf("%s  %s\n", md5sum, text);
	}
	else
		text = g_strdup_printf("%s  %s\n", md5sum, file);
	g_free(md5sum);
	debug_print("md5sum: %s\n", text);
	write(fd, text, strlen(text));
	close(fd);
	g_free(text);
}
