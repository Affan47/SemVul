ast_format_cap_dup(const struct ast_format_cap *cap)
{
	struct ast_format_cap *dst;
	if (cap->nolock) {
		dst = ast_format_cap_alloc_nolock();
	} else {
		dst = ast_format_cap_alloc();
	}
	if (!dst) {
		return NULL;
	}
	ao2_callback(cap->formats, OBJ_NODATA, copy_cb, dst);
	return dst;
}
