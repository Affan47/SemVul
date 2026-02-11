parse_cachedir_option_minsize(SwapDir * sd, const char *option, const char *value, int reconfiguring)
{
    squid_off_t size;

    if (!value)
	self_destruct();

    size = strto_off_t(value, NULL, 10);

    if (reconfiguring && sd->min_objsize != size)
	debug(3, 1) ("Cache dir '%s' min object size now %ld\n", sd->path, (long int) size);

    sd->min_objsize = size;
}
