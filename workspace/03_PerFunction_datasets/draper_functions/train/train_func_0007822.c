lc_strcat_opt(struct lib_context *lc, enum lc_options o,
	      char *arg, const char delim)
{
	char *ret = NULL;

	if (lc_opt_ok(o)) {
		char *a = (char *) OPT_STR(lc, o);
		size_t end = (a ? strlen(a) : 0),
		       len = end + strlen(arg) + ((delim && end) ? 1 : 0) + 1;


		if ((ret = dbg_realloc(a, len))) {
			if (delim && end)
				ret[end++] = delim;

			ret[end] = 0;
			strcat(ret, arg);
			OPT_STR(lc, o) = ret;
		} else {
			dbg_free((char *) OPT_STR(lc, o));
			OPT_STR(lc, o) = ret;
			log_alloc_err(lc, __func__);
		}
	}

	return ret;
}
