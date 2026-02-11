open()
{
	SplitterChannel::open();
	_pParser = new SyslogParser(_queue, this);
	_pListener = new RemoteUDPListener(_queue, _port);
	_parser.start(*_pParser);
	_listener.start(*_pListener);
}
