get_cached_response(const string &url)
{
	string discard_name;
	vector<string> discard_headers;
	return get_cached_response(url, discard_headers, discard_name);
}
