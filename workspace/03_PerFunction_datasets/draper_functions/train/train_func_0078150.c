reset(const String &data, const String &filename)
{
    clear();

    _big_string = data;
    _data = _pos = _big_string.begin();
    _end = _big_string.end();

    if (!filename)
	_filename = "line ";
    else if (filename.back() != ':' && !isspace(filename.back()))
	_filename = filename + ":";
    else
	_filename = filename;
    _original_filename = _filename;
    _lineno = 1;
}
