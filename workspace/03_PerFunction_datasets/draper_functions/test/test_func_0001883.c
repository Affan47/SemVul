safe_fread(void *ptr, size_t nmemb, FILE *stream)
{
	size_t ret;
	char *p = (char*)ptr;

	do {
		clearerr(stream);
		errno = 0;
		ret = fread(p, 1, nmemb, stream);
		p += ret;
		nmemb -= ret;
	} while (nmemb && ferror(stream) && errno == EINTR);

	return p - (char*)ptr;
}
