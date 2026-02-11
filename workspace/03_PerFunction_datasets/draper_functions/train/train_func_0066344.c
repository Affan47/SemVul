sigar_uitoa(char *buf, unsigned int n, int *len)
{
    char *start = buf + UITOA_BUFFER_SIZE - 1;

    *start = 0;

    do {
	*--start = '0' + (n % 10);
        ++*len;
	n /= 10;
    } while (n);

    return start;
}
