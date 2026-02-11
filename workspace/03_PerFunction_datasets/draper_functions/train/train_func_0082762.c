jpeg_read_image(int fd, int len)
{
	struct ast_frame fr;
	int res;
	char buf[65536];
	if (len > sizeof(buf) || len < 0) {
		ast_log(LOG_WARNING, "JPEG image too large to read\n");
		return NULL;
	}
	res = read(fd, buf, len);
	if (res < len) {
		ast_log(LOG_WARNING, "Only read %d of %d bytes: %s\n", res, len, strerror(errno));
	}
	memset(&fr, 0, sizeof(fr));
	fr.frametype = AST_FRAME_IMAGE;
	ast_format_set(&fr.subclass.format, AST_FORMAT_JPEG, 0);
	fr.data.ptr = buf;
	fr.src = "JPEG Read";
	fr.datalen = len;
	return ast_frisolate(&fr);
}
