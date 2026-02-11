printIDtoWordMapping(unordered_map<unsigned, string>& IDsToWords, ostream& os)
{
	for (unordered_map<unsigned, string>::iterator it = IDsToWords.begin(); it != IDsToWords.end(); it++)
	{
		os << it->first << ": " << it->second << endl;
	}
}
