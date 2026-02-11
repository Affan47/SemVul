writeToDevice(char c)
{
	poco_assert_dbg (_pOstr);

	_buffer[_pos++] = (unsigned char) c;
	if (_sequenceLength == 0 || _sequenceLength == _pos)
	{
		int n = _inEncoding.queryConvert(_buffer, _pos);
		if (-1 <= n)
		{
			int uc = n;
			if (-1 == n)
			{
				++_errors;
				return -1;
			}
			int n = _outEncoding.convert(uc, _buffer, sizeof(_buffer));
			if (n == 0) n = _outEncoding.convert(_defaultChar, _buffer, sizeof(_buffer));
			poco_assert_dbg (n <= sizeof(_buffer));
			_pOstr->write((char*) _buffer, n);
			_sequenceLength = 0;
			_pos = 0;
		}
		else
		{
			_sequenceLength = -n;
		}
	}

	return charToInt(c);
}
