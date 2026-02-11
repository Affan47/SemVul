SanitizeXML(string in_str) {

	string ret;
	for (unsigned int x = 0; x < in_str.length(); x++) {
		if (in_str[x] == '&')
			ret += "&amp;";
		else if (in_str[x] == '<')
			ret += "&lt;";
		else if (in_str[x] == '>')
			ret += "&gt;";
		else
			ret += in_str[x];
	}

	return ret;
}
