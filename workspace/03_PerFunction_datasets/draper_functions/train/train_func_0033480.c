write_handler(const String &str, Element *e, void *thunk, ErrorHandler *errh)
{
    ICMPIPEncap *i = static_cast<ICMPIPEncap *>(e);
    IPAddress a;
    if (!IPAddressArg().parse(str, a))
	return errh->error("syntax error");
    if (thunk)
	i->_dst = a;
    else
	i->_src = a;
    return 0;
}
