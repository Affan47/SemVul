getPath() const
{
	std::string::size_type p = ResolvedName.rfind(sPathSep);
	if (p == std::string::npos)
		p = 0;
	return std::string(ResolvedName,0,p);
}
