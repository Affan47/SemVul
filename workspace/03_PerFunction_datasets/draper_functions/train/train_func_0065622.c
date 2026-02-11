new_filter_icmp(enum filtertype type, const char *matchstr)
{
    struct filter *f;
    if ((f = __new_filter(type))) {
	f->u.icmp = strdup(matchstr);
    }
    return f;
}
