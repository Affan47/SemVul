prefix_with_slash(const String &str, const char *slash,
		  IPAddress &result_addr, IPAddress &result_mask,
		  const ArgContext &args)
{
    unsigned char addr[4];
    int nbytes;
    if (IPAddressArg::basic_parse(str.begin(), slash, addr, nbytes) == slash)
	;
#if !CLICK_TOOL
    else if (args.context()
	     && AddressInfo::query_ip(str.substring(str.begin(), slash), addr, args.context()))
	nbytes = 4;
#endif
    else
	return false;

    int l = -1;
    IPAddress mask;
    if (IntArg(10).parse(str.substring(slash + 1, str.end()), l)
	&& l >= 0 && l <= 32)
	mask = IPAddress::make_prefix(l);
    else if (!IPAddressArg::parse(str.substring(slash + 1, str.end()), mask, args))
	return false;


    if (nbytes < 4 && (mask & IPAddress::make_prefix(nbytes * 8)) != mask)
	return false;

    memcpy(result_addr.data(), addr, 4);
    result_mask = mask;
    return true;
}
