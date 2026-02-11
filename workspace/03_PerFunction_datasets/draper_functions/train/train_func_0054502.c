str_i_starts_with(const string& str, const char* find) {
	int idx = 0;
	int len = str.length();
	while (idx < len && toupper(find[idx]) == toupper(str[idx])) {
		idx++;
	}
	return find[idx] == 0;
}
