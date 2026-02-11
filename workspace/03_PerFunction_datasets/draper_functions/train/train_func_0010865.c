name(struct lib_context *lc, struct asr *asr)
{
	size_t len;
	char *ret;

	if ((ret = dbg_malloc((len = _name(lc, asr, NULL, 0) + 1))))
		_name(lc, asr, ret, len);
	else
		log_alloc_err(lc, handler);

	return ret;
}
