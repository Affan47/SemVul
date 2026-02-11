setup_packet()
{
    if (_packet)
	_packet->kill();

    if (_datasize < 0)
	_packet = Packet::make(_data.data(), _data.length());
    else if (_datasize <= _data.length())
	_packet = Packet::make(_data.data(), _datasize);
    else {

	StringAccum sa;
	while (sa.length() < _datasize)
	    sa << _data;
	_packet = Packet::make(sa.data(), _datasize);
    }
}
