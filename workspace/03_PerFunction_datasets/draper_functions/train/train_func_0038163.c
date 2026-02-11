addItem(const char *item) {
	if (((currentSize > 0) && (strcmp(buf, item) != 0)) || (currentSize == 0)) {
		memmove(buf + len + 1, buf, (size - 1)*(len + 1));
		if ((signed)strlen(item) <= len) {
			strcpy(buf, item);
		} else {
			strncpy(buf, item, len);
			buf[len] = '\0';
		}
		if (currentSize < size) {
			currentSize++;
		}
		current = -1;
	}
}
