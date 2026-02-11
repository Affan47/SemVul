search_label(char *nm)
{
	std::map<std::string,Uc_label*>::iterator iter;
	iter = labels.find(nm);
	if (iter != labels.end())
		return iter->second;
	return 0;
}
