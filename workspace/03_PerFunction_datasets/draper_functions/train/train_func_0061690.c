c_str()
{
    if (_len < _cap || grow(_len))
	_s[_len] = '\0';
    return reinterpret_cast<char *>(_s);
}
