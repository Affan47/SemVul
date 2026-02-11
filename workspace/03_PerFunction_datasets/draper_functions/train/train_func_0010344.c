configure(Vector<String> &conf, ErrorHandler *errh)
{
    unsigned dscp_val;
    if (Args(conf, this, errh).read_mp("DSCP", dscp_val).complete() < 0)
	return -1;
    if (dscp_val > 0x3F)
	return errh->error("diffserv code point out of range");

    _dscp = (dscp_val << 2);
    return 0;
}
