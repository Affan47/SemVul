sig_fromfile(char *path, isc_buffer_t *iscbuf) {
	size_t		rval;
	size_t		len;
	FILE		*fp;
	unsigned char	val;
	char		*p;
	char		*buf;
	isc_result_t	isc_result;
	off_t		size;

	isc_result = isc_stdio_open(path, "rb", &fp);
	if (isc_result != ISC_R_SUCCESS) {
		t_info("open failed, result: %s\n",
		       isc_result_totext(isc_result));
		return(1);
	}

	isc_result = isc_file_getsizefd(fileno(fp), &size);
	if (isc_result != ISC_R_SUCCESS) {
		t_info("stat %s failed, result: %s\n",
		       path, isc_result_totext(isc_result));
		isc_stdio_close(fp);
		return(1);
	}

	buf = (char *) malloc((size + 1) * sizeof(char));
	if (buf == NULL) {
		t_info("malloc failed, errno == %d\n", errno);
		isc_stdio_close(fp);
		return(1);
	}

	len = (size_t)size;
	p = buf;
	while (len != 0U) {
		isc_result = isc_stdio_read(p, 1, len, fp, &rval);
		if (isc_result == ISC_R_SUCCESS) {
			len -= rval;
			p += rval;
		} else {
			t_info("read failed %d, result: %s\n",
			       (int)rval, isc_result_totext(isc_result));
			(void) free(buf);
			(void) isc_stdio_close(fp);
			return(1);
		}
	}
	isc_stdio_close(fp);

	p = buf;
	len = size;
	while (len > 0U) {
		if ((*p == '\r') || (*p == '\n')) {
			++p;
			--len;
			continue;
		} else if (len < 2U)
		       goto err;
		if (('0' <= *p) && (*p <= '9'))
			val = *p - '0';
		else if (('A' <= *p) && (*p <= 'F'))
			val = *p - 'A' + 10;
		else
			goto err;
		++p;
		val <<= 4;
		--len;
		if (('0' <= *p) && (*p <= '9'))
			val |= (*p - '0');
		else if (('A' <= *p) && (*p <= 'F'))
			val |= (*p - 'A' + 10);
		else
			goto err;
		++p;
		--len;
		isc_buffer_putuint8(iscbuf, val);
	}
	(void) free(buf);
	return(0);

 err:
	(void) free(buf);
	return (1);
}
