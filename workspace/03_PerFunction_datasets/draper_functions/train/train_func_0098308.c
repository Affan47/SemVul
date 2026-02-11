ast_ext_ctx(const char *src, char **ext, char **ctx)
{
	struct chan_oss_pvt *o = find_desc(oss_active);

	if (ext == NULL || ctx == NULL)
		return NULL;

	*ext = *ctx = NULL;

	if (src && *src != '\0')
		*ext = ast_strdup(src);

	if (*ext == NULL)
		return NULL;

	if (!o->overridecontext) {

		*ctx = strrchr(*ext, '@');
		if (*ctx)
			*(*ctx)++ = '\0';
	}

	return *ext;
}
