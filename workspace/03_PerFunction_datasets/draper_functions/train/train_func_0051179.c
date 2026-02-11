zCalloc (size_t nobj, size_t size, const char *str) {
	void *buffer;

	zTrace3("zCalloc (%d, %d) from %s", nobj, size, str);
	if ((buffer = calloc(nobj, size)) == NULL) zDie("calloc %s", str);
	return buffer;
}
