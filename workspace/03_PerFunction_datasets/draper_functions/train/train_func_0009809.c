format_object_header(char *hdr, size_t n, git_rawobj *obj)
{
	const char *type_str = git_object_type2string(obj->type);
	int len = snprintf(hdr, n, "%s %"PRIuZ, type_str, obj->len);

	assert(len > 0);
	assert(((size_t) len) < n);

	if (len < 0 || ((size_t) len) >= n)
		return GIT_ERROR;
	return len+1;
}
