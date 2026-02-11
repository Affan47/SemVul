configure(Vector<String> &conf, ErrorHandler *errh)
{
    _max = -1;
    int ret = Args(conf, this, errh)
	.read_mp("PREFIX", IPPrefixArg(true), _ip, _mask)
	.read_p("LIMIT", _max).complete();

    if(_max >= 0){
	_addrs = new IPAddress [_max] ();

	int i;
	for(i = 0; i < _max; i++)
	    _addrs[i] = pick();
    }

    return(ret);
}
