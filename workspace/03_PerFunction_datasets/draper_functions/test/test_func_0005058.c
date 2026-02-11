forName(const std::string& name, bool requireIPv6)
{
	NetworkInterfaceList ifs = list();
	for (NetworkInterfaceList::const_iterator it = ifs.begin(); it != ifs.end(); ++it)
	{
		if (it->name() == name && ((requireIPv6 && it->supportsIPv6()) || !requireIPv6))
			return *it;
	}
	throw InterfaceNotFoundException(name);
}
