Mono_Posix_Syscall_strerror_r (int errnum, char *buf, mph_size_t n)
{
	char *r;
	char ebuf [sizeof(mph_unknown)];
	size_t len;
	size_t blen;

	mph_return_if_size_t_overflow (n);


#if PLATFORM_ANDROID


	if (strerror_r (errnum, ebuf, sizeof(ebuf)) == -1) {


		errno = EINVAL;
		return -1;
	}
	r = ebuf;
#else
	r = strerror_r (errnum, ebuf, sizeof(ebuf));
#endif
	if (!r) {
		errno = EINVAL;
		return -1;
	}
	len = strlen (r);

	if (r == ebuf ||
			strncmp (r, mph_unknown, mph_min (len, sizeof(mph_unknown))) == 0) {
		errno = EINVAL;
		return -1;
	}


	blen = (size_t) n;
	if ((len+1) > blen) {
		errno = ERANGE;
		return -1;
	}

	strncpy (buf, r, len);
	buf[len] = '\0';

	return 0;
}
