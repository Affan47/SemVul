getCookies(std::vector<HTTPCookie>& cookies) const
{
	cookies.clear();
	NameValueCollection::ConstIterator it = find(SET_COOKIE);
	while (it != end() && it->first == SET_COOKIE)
	{
		NameValueCollection nvc;
		splitParameters(it->second.begin(), it->second.end(), nvc);
		cookies.push_back(HTTPCookie(nvc));
		++it;
	}
}
