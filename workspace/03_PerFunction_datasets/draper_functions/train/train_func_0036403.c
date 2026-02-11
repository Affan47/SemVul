attr_remove(const char *path, const char *attrname, int flags)
{
	int c, compat;
	char name[MAXNAMELEN+16];

	for (compat = 0; compat < 2; compat++) {
		if ((c = api_convert(name, attrname, flags, compat)) < 0)
			return c;
		if (flags & ATTR_DONTFOLLOW)
			c = lremovexattr(path, name);
		else
			c = removexattr(path, name);
		if (c < 0 && (errno == ENOATTR || errno == ENOTSUP))
			continue;
		break;
	}
	return c;
}
