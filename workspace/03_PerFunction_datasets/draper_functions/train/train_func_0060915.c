add_string_str(const char *s)
{
	int l = strlen(s) + 1;
	if(_nstring + l > _nastring)
	{
		_nastring += MAX(128, l);
		_string = xrealloc(_string, _nastring * sizeof(_string[0]));
	}
	memcpy(_string+_nstring, s, l);
	_nstring += l-1;
}
