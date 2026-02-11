load() throw(ParserError) {

	if (getLocation()->isStdin()) {
		load(cin);
	} else {
		ifstream input;
		input.open(getLocation()->getFullPath().c_str());
		if (!input.is_open()) {
			g_throw_parser_error("file not found: '", getLocation()->getName().c_str(), "'");
		}
		load(input);
		input.close();
	}
}
