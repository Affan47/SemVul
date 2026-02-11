string_to_list (std::string input, std::list <std::string> & output) {
	std::string item;
	bool space = true;
	output.clear ();

	for (unsigned int n = 0; n < input.size (); n++) {
		if (isspace (input [n])) {
			if (! space) {
				output.push_back (item);
				item.erase ();
				space = true;
			}
		} else {
			item += input [n];
			space = false;
		}
	}

	if (! space) {
		output.push_back (item);
	}
}
