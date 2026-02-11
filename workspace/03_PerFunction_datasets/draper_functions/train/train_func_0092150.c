command(const char* format) {
    int index = 0;
    while (index < _nformats) {
	if (strcmp(format, _formats[index])==0)
	    break;
	index++;
    }
    if (index==_nformats)
	return "ghostview";
    else {
	if (_commands)
	    return _commands[index];
	else
	    return _formats[index];
    }
}
