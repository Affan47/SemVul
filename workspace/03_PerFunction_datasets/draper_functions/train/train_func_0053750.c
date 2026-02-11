writeToDevice(char c)
{
	switch (c)
	{
	case '\r':
		_state = ST_CR;
		break;
	case '\n':
		if (_state == ST_CR)
			_state = ST_CR_LF;
		else
			_state = ST_DATA;
		break;
	case '.':
		if (_state == ST_CR_LF)
			_state = ST_CR_LF_DOT;
		else
			_state = ST_DATA;
		break;
	default:
		_state = ST_DATA;
	}
	if (_state == ST_DATA)
	{
		if (!_buffer.empty())
		{
			_pOstr->write(_buffer.data(), (std::streamsize) _buffer.length());
			_buffer.clear();
		}
		_pOstr->put(c);
	}
	else if (_state == ST_CR_LF_DOT)
	{
		_pOstr->write("\r\n..", 4);
		_state = ST_DATA;
		_buffer.clear();
	}
	else _buffer += c;
	return charToInt(c);
}
