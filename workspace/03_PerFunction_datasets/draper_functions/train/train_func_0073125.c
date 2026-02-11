IsAWordChar(const int  ch) {
	return (ch < 0x80) && (isalnum(ch) || ch == '.' || ch == '_' || ch == '$' || ch == ':');
}
