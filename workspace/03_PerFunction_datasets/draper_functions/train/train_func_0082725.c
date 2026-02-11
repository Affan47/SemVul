http_range_extract_first(
	const char *field, const char *value, filesize_t size, const char *vendor,
	filesize_t *start, filesize_t *end)
{
	struct http_range_extract_ctx ctx;
	bool ok;

	ZERO(&ctx);
	ok = http_range_parser(field, value, size, vendor, http_range_got, &ctx);

	if (!ok || !ctx.has_range)
		return HTTP_RANGE_NONE;

	if (start != NULL)	*start = ctx.start;
	if (end != NULL)	*end = ctx.end;

	return ctx.has_multi ? HTTP_RANGE_MULTI : HTTP_RANGE_SINGLE;
}
