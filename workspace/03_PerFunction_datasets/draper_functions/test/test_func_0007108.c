git_oid_fromstrn(git_oid *out, const char *str, size_t length)
{
	size_t p;

	if (length > GIT_OID_HEXSZ)
		length = GIT_OID_HEXSZ;

	if (length % 2)
		length--;

	for (p = 0; p < length; p += 2) {
		int v = (from_hex[(unsigned char)str[p + 0]] << 4)
		       | from_hex[(unsigned char)str[p + 1]];

		if (v < 0)
			return git__throw(GIT_ENOTOID, "Failed to generate sha1. Given string is not a valid sha1 hash");

		out->id[p / 2] = (unsigned char)v;
	}

	for (; p < GIT_OID_HEXSZ; p += 2)
		out->id[p / 2] = 0x0;

	return GIT_SUCCESS;
}
