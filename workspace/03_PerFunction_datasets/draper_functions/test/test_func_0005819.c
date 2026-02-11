yrequire_library(const Lexeme &lexeme, const String &value)
{
    if (_router->scope().depth()) {
	lerror(lexeme, "%<require library%> must be used at file scope");
	return;
    }

    String dir = _file._filename;
    int pos = dir.find_right('/');
    if (pos > 0)
	dir = dir.substring(0, pos);
    else
	dir = ".";
    String fn = clickpath_find_file(value, "conf", dir, 0);
    if (!fn) {
	lerror(lexeme, "library %<%#s%> not found in CLICKPATH/conf", fn.c_str());
	return;
    }

    for (String *it = _libraries.begin(); it != _libraries.end(); ++it)
	if (*it == fn)
	    return;
    _libraries.push_back(fn);

    LandmarkErrorHandler lerrh(_errh, _file.landmark());
    int before = lerrh.nerrors();
    String data = file_string(fn, &lerrh);
    if (lerrh.nerrors() != before)
	return;

    FileState old_file(_file);
    _file = FileState(data, fn);
    while (ystatement(0))
	;
    _file = old_file;
}
