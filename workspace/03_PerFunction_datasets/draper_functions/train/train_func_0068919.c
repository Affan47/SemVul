writeToDevice(char c)
{
	++_chars;
	if (_pos++ == 0) ++_lines;
	if (c == '\n') _pos = 0;
	if (_pOstr) _pOstr->put(c);
	return charToInt(c);
}
