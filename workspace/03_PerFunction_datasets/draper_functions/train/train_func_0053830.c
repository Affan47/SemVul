operator<<(WriteStream & ws, docstring const & s)
{

	size_t const first =
		(s.length() > 0 && (s[0] != '\n' || ws.canBreakLine())) ? 0 : 1;


	if (s.length() <= first)
		return ws;

	if (ws.pendingBrace()) {
		ws.os() << '}';
		ws.pendingBrace(false);
		ws.pendingSpace(false);
		ws.textMode(true);
	} else if (ws.pendingSpace()) {
		if (isAlphaASCII(s[first]))
			ws.os() << ' ';
		else if (s[first] == ' ' && ws.textMode())
			ws.os() << '\\';
		ws.pendingSpace(false);
	}
	ws.os() << s.substr(first);
	int lf = 0;
	char_type lastchar = 0;
	docstring::const_iterator dit = s.begin() + first;
	docstring::const_iterator end = s.end();
	for (; dit != end; ++dit) {
		lastchar = *dit;
		if (lastchar == '\n')
			++lf;
	}
	ws.addlines(lf);
	ws.canBreakLine(lastchar != '\n');
	return ws;
}
