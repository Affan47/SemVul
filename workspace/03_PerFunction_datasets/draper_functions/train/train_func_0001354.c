inPaths(string const& path, string const& list)
{
	std::istringstream s(list + ":");
	string buf;
	while (getline(s, buf, ':') && buf.size()) {
		if (buf == "/" || !fnmatch(buf.c_str(), path.c_str(), 0) || !path.find(buf + "/"))
			return true;
	}
	return false;
}
