listkeys(const string &key,vector<string> &vs, bool longformat) const
{
	string s(key);
	s+="/";

	for(std::vector<XMLnode*>::const_iterator it=nodelist.begin();
		it!=nodelist.end(); ++it)
	{
		if(!longformat)
			vs.push_back((*it)->id);
		else
			vs.push_back(s + (*it)->id);
	}
}
