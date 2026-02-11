stdStringIsEqualCI(const std::string &s1, const std::string &s2)
{
	std::string ns1(s1);
	std::string ns2(s2);
	std::transform(ns1.begin(), ns1.end(), ns1.begin(), tolower);
	std::transform(ns2.begin(), ns2.end(), ns2.begin(), tolower);
	return ns1 == ns2;
}
