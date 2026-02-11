addrinput(char *buf, size_t max_size)
{
    extern char *addrptr;
    size_t n;

    n = strlen(addrptr) < max_size ? strlen(addrptr) : max_size;
    if (n > 0) {
	memcpy(buf, addrptr, n);
	addrptr += n;
    }
    return n;
}
