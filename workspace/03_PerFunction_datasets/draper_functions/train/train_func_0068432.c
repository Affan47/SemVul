Log(const std::string& String)
{
	Entries.push_back(String);

	while (Entries.size()>m_cMaxSize)
		Entries.erase(Entries.begin());
}
