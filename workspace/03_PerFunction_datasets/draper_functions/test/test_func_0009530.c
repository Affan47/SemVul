nls_strcmp(nls_string *s1, nls_string *s2)
{
	if (s1->ns_hash != s2->ns_hash) {
		return s1->ns_hash - s2->ns_hash;
	}
	if (s1->ns_len != s2->ns_len) {
		return s1->ns_len - s2->ns_len;
	}
	return strncmp(s1->ns_bufp, s2->ns_bufp, s1->ns_len);
}
