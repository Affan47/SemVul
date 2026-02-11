unparse_proto(int ip_p, bool prepend)
{
    if (String s = NameInfo::revquery_int(NameInfo::T_IP_PROTO, 0, ip_p))
	return s;
    else if (prepend)
	return String::make_stable("protocol ", 9) + String(ip_p);
    else
	return String(ip_p);
}
