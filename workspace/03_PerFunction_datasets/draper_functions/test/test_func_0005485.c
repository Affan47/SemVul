name_len(const char *xattr_name, int xattr_name_len)
{
	int len = xattr_name_len + 1;

	if (!is_known_namespace(xattr_name))
		len += XATTR_MAC_OSX_PREFIX_LEN;

	return len;
}
