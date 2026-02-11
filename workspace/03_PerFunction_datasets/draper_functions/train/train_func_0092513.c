font_str_to_code(map<string, unsigned int>& charcodes, const char* name) {
	string my_name = name;
	map<string, unsigned int>::iterator it = charcodes.find(my_name);
	if (it == charcodes.end()) {
		printf("error: can't find code point for '%s'\n", name);
		exit(-1);
	}
	return it->second;
}
