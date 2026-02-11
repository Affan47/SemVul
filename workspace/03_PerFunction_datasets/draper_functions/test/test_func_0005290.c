configure(Vector<String> &conf, ErrorHandler *errh)
{
    bool stop = false;
    _active = _zero = true;
    _multipacket = _timing = false;
    String link = "input";

    if (Args(conf, this, errh)
	.read_mp("FILENAME", FilenameArg(), _ff.filename())
	.read("STOP", stop)
	.read("ACTIVE", _active)
	.read("ZERO", _zero)
	.read("MULTIPACKET", _multipacket)
	.read("LINK", WordArg(), link)
	.read("TIMING", _timing)
	.complete() < 0)
	return -1;

    _stop = stop;
    link = link.lower();
    if (link == "input")
	_link = 0;
    else if (link == "output")
	_link = 1;
    else if (link == "both")
	_link = 2;
    else
	return errh->error("'LINK' should be 'input', 'output', or 'both'");
    return 0;
}
