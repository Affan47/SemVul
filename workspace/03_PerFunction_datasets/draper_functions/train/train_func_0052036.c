extract(const std::string& subject, std::string::size_type offset, std::string& str, int options) const
{
	Match mtch;
	int rc = match(subject, offset, mtch, options);
	if (mtch.offset != std::string::npos)
		str.assign(subject, mtch.offset, mtch.length);
	else
		str.clear();
	return rc;
}
