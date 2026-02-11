chirp_client_lremovexattr(struct chirp_client * c, const char *path, const char *name, time_t stoptime)
{
	char safepath[CHIRP_LINE_MAX];
	url_encode(path, safepath, sizeof(safepath));
	INT64_T result = simple_command(c, stoptime, "lremovexattr %s %s\n", safepath, name);
	if(result == -1 && errno == EINVAL)
		errno = ENOATTR;
	return result;
}
