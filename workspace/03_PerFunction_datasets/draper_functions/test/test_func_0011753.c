updateKeywords(const std::vector<size_t> &messages,
				   const std::list<std::string> &keywords,
				   bool setOrChange,

				   bool changeTo)
{
	set<string> keySet;

	keySet.insert(keywords.begin(), keywords.end());
	return updateKeywords(messages, keySet, setOrChange, changeTo);
}
