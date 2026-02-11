configure(Vector<String> &conf, ErrorHandler *errh)
{
    return Args(conf, this, errh)
	.read_mp("SRC", _src)
	.read_mp("DST", _dst)
	.read_mp("PREFIX", IPPrefixArg(), _what, _mask)
	.read_mp("METRIC", _metric).complete();
}
