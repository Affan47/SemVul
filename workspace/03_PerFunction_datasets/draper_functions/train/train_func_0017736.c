initramfs_mkdirs(const char *filename, void *buffer,
			       size_t buflen)
{
    const char *p = filename;
    char *bp = buffer;
    int len;
    size_t bytes = 0;
    int pad;

    while ((p = strchr(p, '/'))) {
	if (p != filename && p[-1] != '/') {
	    len = p - filename;
	    bytes += ((sizeof(struct cpio_header) + len + 1) + 3) & ~3;
	}
	p++;
    }

    if (buflen >= bytes) {
	p = filename;
	while ((p = strchr(p, '/'))) {
	    if (p != filename && p[-1] != '/') {
		len = p - filename;
		bp += sprintf(bp, "070701%08x%08x%08x%08x%08x%08x%08x%08x%08x"
			      "%08x%08x%08x%08x", next_ino++, S_IFDIR | 0755,
			      0, 0, 1, 0, 0, 0, 1, 0, 1, len + 1, 0);
		memcpy(bp, filename, len);
		bp += len;
		pad = (-(sizeof(struct cpio_header) + len) & 3) + 1;
		memset(bp, 0, pad);
		bp += pad;
	    }
	}
    }

    return bytes;
}
