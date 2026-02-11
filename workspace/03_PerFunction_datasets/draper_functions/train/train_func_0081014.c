zlib_deflate(ZLibData* d, int flush)
{
    int res = Z_OK;

    if ((d->bin == NULL) && (zlib_output_init(d) < 0)) {
	errno = ENOMEM;
	return Z_ERRNO;
    }

    while ((driver_sizeq(d->port) > 0) && (res != Z_STREAM_END)) {
	int vlen;
	SysIOVec* iov = driver_peekq(d->port, &vlen);
	int len;

	d->s.next_in = iov[0].iov_base;
	d->s.avail_in = iov[0].iov_len;

	while((d->s.avail_in > 0) && (res != Z_STREAM_END)) {
	    if ((res = deflate(&d->s, Z_NO_FLUSH)) < 0) {
		return res;
	    }
	    if (d->s.avail_out == 0) {
		zlib_output(d);
	    }
	}
	len = iov[0].iov_len - d->s.avail_in;
	if (d->want_crc) {
	    d->crc = crc32(d->crc, iov[0].iov_base, len);
	}
	driver_deq(d->port, len);
    }

    if (flush != Z_NO_FLUSH) {
	if ((res = deflate(&d->s, flush)) < 0) {
	    return res;
	}
	if (flush == Z_FINISH) {
	    while (d->s.avail_out < d->binsz) {
		zlib_output(d);
		if (res == Z_STREAM_END) {
		    break;
		}
		if ((res = deflate(&d->s, flush)) < 0) {
		    return res;
		}
	    }
	} else {
	    while (d->s.avail_out == 0) {
	       zlib_output(d);
	       if ((res = deflate(&d->s, flush)) < 0) {
		  return res;
	       }
	    }
	    if (d->s.avail_out < d->binsz) {
	       zlib_output(d);
	    }
	}
    }
    return res;
}
