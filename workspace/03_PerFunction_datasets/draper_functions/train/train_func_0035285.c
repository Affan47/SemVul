expand_escapes(const char *line, SERVER_REC *server,
			    WI_ITEM_REC *item)
{
	char *ptr, *ret;
        int chr;

	ret = ptr = g_malloc(strlen(line)+1);
	for (; *line != '\0'; line++) {
		if (*line != '\\') {
			*ptr++ = *line;
			continue;
		}

		line++;
		if (*line == '\0') {
			*ptr++ = '\\';
			break;
		}

		chr = expand_escape(&line);
		if (chr == '\r' || chr == '\n') {


			if (ret != ptr) {
				*ptr = '\0';
				signal_emit("send text", 3, ret, server, item);
				ptr = ret;
			}
		} else if (chr != -1) {

			*ptr++ = chr;
		} else {

			*ptr++ = '\\';
			*ptr++ = *line;
		}
	}

	*ptr = '\0';
	return ret;
}
