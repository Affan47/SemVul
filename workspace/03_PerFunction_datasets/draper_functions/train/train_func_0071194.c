additems(std::vector<std::string> *items, std::string path, int depth) {
	if(depth < 0) return;


	char **expanded = reader_expand (path.c_str ());

	if (expanded) {
		char **c_uri = expanded;

		while (*c_uri)
		    additems (items, *(c_uri++), depth-1);

		reader_free_expanded (expanded);
	} else {
		items->push_back(path);
	}
}
