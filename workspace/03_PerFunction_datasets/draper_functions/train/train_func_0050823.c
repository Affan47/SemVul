ast_format_cap_iscompatible(const struct ast_format_cap *cap, const struct ast_format *format)
{
	struct ast_format *f;
	struct ast_format_cap *tmp_cap = (struct ast_format_cap *) cap;

	if (!tmp_cap) {
		return 0;
	}

	f = ao2_find(tmp_cap->formats, format, OBJ_POINTER);
	if (f) {
		ao2_ref(f, -1);
		return 1;
	}

	return 0;
}
