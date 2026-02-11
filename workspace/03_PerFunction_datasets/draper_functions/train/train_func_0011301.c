getLocationsAtVersion(unsigned version)
{
	if (locationsInDoc.find(version) != locationsInDoc.end())
		return locationsInDoc[version];
	return set<int>();
}
