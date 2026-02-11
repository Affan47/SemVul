name(struct lib_context *lc, struct raid_dev *rd, unsigned int subset)
{
	size_t len;
	char *ret, *suffix;
	struct via *via = META(rd, via);

	if (!(suffix = _name_suffix(via)))
		return NULL;

	subset = subset && (VIA_RAID_TYPE(via) == VIA_T_RAID01);
	if ((ret = dbg_malloc((len = _name(lc, via, NULL, 0,
					   suffix, subset) + 1)))) {
		_name(lc, via, ret, len, suffix, subset);
		mk_alpha(lc, ret + HANDLER_LEN, len - HANDLER_LEN -
			 (subset ? 3 : 1));
	}
	else
		log_alloc_err(lc, handler);

	dbg_free(suffix);

	return ret;
}
