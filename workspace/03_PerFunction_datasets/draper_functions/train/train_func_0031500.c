byte_copy(unsigned char *dst, const unsigned char *src, size_t n) {
    if (n && dst && dst != src) {
#if HAVE_BROKEN_MEMMOVE
	size_t i;

	if (dst >= src + n || dst + n <= src) {
	    memcpy(dst, src, n);
	}
	else if (dst < src) {
	    for (i = 0; i < n; i++) {
		dst[i] = src[i];
	    }
	}
	else {
	    for (i = n; --i; ) {
		dst[i] = src[i];
	    }
	}
#else
	memmove(dst, src, n);
#endif
    }
    return n;
}
