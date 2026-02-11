findAppConfigFile(const std::string& appName, const std::string& extension, Path& path) const
{
	poco_assert (!appName.empty());

	Path p(appName);
	p.setExtension(extension);
	bool found = findFile(p);
	if (!found)
	{
#if defined(_DEBUG)
		if (appName[appName.length() - 1] == 'd')
		{
			p.setBaseName(appName.substr(0, appName.length() - 1));
			found = findFile(p);
		}
#endif
	}
	if (found)
		path = p;
	return found;
}
