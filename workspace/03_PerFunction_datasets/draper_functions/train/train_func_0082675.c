dispatch_read(fbuf, buf, size)
    fbuf_t *fbuf;
    char *buf;
    int size;
{
    int count, remaining = size, total;

    total = count = fbuf->iptr - fbuf->uend;
    if (count) {
	if (remaining < count) count = remaining;
	memcpy(buf, fbuf->uend, count);
	remaining -= count;
	fbuf->uend += count;
	buf += count;
    }
    if (remaining > 0) {
	do {
	    count = fill_buf(fbuf, buf, remaining);
	    if (count == 0) break;
	    if (count < 0) { (*err_proc)(DISPATCH_READ_ERR); return (count); }
	    total += count;
	    buf += count;
	    remaining -= count;
	} while ((remaining > 0) && !fbuf->nonblocking);
    }

    return (total);
}
