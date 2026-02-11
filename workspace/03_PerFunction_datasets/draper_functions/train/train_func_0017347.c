ns_name_compress(const char *src, u_char *dst, size_t dstsiz,
		 const u_char **dnptrs, const u_char **lastdnptr)
{
	u_char tmp[NS_MAXCDNAME];

	if (ns_name_pton(src, tmp, sizeof tmp) == -1)
		return (-1);
	return (ns_name_pack(tmp, dst, dstsiz, dnptrs, lastdnptr));
}
