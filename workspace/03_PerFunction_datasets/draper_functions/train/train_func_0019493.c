icmFileMem_read(
icmFile *pp,
void *buffer,
size_t size,
size_t count
) {
	icmFileMem *p = (icmFileMem *)pp;
	size_t len;

	len = ssat_mul(size, count);
	if (len > (p->end - p->cur)) {
		if (size > 0)
			count = (p->end - p->cur)/size;
		else
			count = 0;
	}
	len = size * count;
	if (len > 0)
		memmove(buffer, p->cur, len);
	p->cur += len;
	return count;
}
