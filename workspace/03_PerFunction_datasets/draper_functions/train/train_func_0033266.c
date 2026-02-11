path_expand (string path)
{
        if (path.empty()) {
                return path;
        }


        if (path[0] == '~') {
                if (path.length() == 1) {
                        return Glib::get_home_dir();
                }

                if (path[1] == '/') {
                        path.replace (0, 1, Glib::get_home_dir());
                } else {

                }
        }


	regex_t compiled_pattern;
	const int nmatches = 100;
	regmatch_t matches[nmatches];

	if (regcomp (&compiled_pattern, "\\$([a-zA-Z_][a-zA-Z0-9_]*|\\{[a-zA-Z_][a-zA-Z0-9_]*\\})", REG_EXTENDED)) {
		std::cerr << "bad regcomp\n";
                return path;
        }

	while (true) {

		if (regexec (&compiled_pattern, path.c_str(), nmatches, matches, 0)) {
			break;
		}


		string match = path.substr (matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so);


                if (match[1] == '{') {

                        match = match.substr (2, match.length() - 3);
                }

		char* matched_value = getenv (match.c_str());

		if (matched_value) {
			path.replace (matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so, matched_value);
		} else {
			path.replace (matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so, string());
                }


	}

	regfree (&compiled_pattern);


	char buf[PATH_MAX+1];

	if (realpath (path.c_str(), buf)) {
		return buf;
	} else {
		return string();
	}
}
