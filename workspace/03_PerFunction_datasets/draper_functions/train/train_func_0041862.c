parse(const String &str,
				    Vector<IPAddress> &result_bad_src,
				    Vector<IPAddress> &result_good_dst,
				    Args &args)
{
    String arg(str);
    IPAddress ip, mask;
    int nwords = 0;
    while (String word = cp_shift_spacevec(arg)) {
	++nwords;
	if (IPPrefixArg(true).parse(word, ip, mask, args)) {
	    result_bad_src.push_back((ip & mask) | ~mask);
	    result_good_dst.push_back(ip);
	} else
	    return false;
    }
    if (nwords == result_bad_src.size()) {
	result_bad_src.push_back(IPAddress(0));
	result_bad_src.push_back(IPAddress(0xFFFFFFFFU));
	return true;
    }
    args.error("out of memory");
    return false;
}
