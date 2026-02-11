add_token(list<string> &token_list, const string &token) {
	if (token.size() > 0) {
		if (token[0] != ' ') {
			token_list.push_back(token);

		}
	}
}
