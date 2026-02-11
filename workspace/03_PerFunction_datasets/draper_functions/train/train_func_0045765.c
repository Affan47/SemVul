StripWhiteSpace(QString& str) {
	while (str.size() > 0 && (str[str.size()-1] == ' '  ||
	                          str[str.size()-1] == '\n' ||
	                          str[str.size()-1] == '\r')) {
		str.truncate(str.size()-1);
	}
}
