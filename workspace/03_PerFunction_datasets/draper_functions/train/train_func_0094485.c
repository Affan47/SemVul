prefix_mask_part(const String &str, IPAddress *result
		 CP_CONTEXT)
{
    int p;
    if (cp_integer(str.begin(), str.end(), 10, &p) == str.end()
	&& p >= 0 && p <= 32) {
	*result = IPAddress::make_prefix(p);
	return true;
    } else
	return cp_ip_address(str, result  CP_PASS_CONTEXT);
}
