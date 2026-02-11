hasLocationsAtVersion(unsigned version)
{
	if (locationsInDoc.find(version) != locationsInDoc.end())
		return locationsInDoc[version].size() > 0;
	return false;
}
