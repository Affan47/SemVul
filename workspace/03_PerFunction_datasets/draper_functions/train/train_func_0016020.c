wrap_apol_str_to_internal_ip(char *str) {
		apol_ip_t *ip = NULL;
		BEGIN_EXCEPTION
		ip = calloc(1, sizeof(*ip));
		int retv = 0;
		if (!ip) {
			SWIG_exception(SWIG_MemoryError, "Out of memory");
		}
		retv = apol_str_to_internal_ip(str, ip->ip);
		if (retv < 0) {
			free(ip);
			SWIG_exception(SWIG_RuntimeError, "Could not convert string to IP");
		}
		ip->proto = retv;
		END_EXCEPTION
	fail:
		return ip;
	}
