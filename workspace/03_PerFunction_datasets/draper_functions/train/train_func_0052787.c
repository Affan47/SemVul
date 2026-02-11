find_separator(const String& s) {
    int n = s.length();
    for (int i = 0; i < n; i++) {
	char c = s[i];
	if (c == '*' || c == '.') {
	    return i;
	}
    }
    return -1;
}
