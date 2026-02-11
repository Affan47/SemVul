addAll(const vector<Edge*> &edgeColl)
{
    for (std::size_t i=0, s=edgeColl.size(); i<s ; ++i)
	{
		add(edgeColl[i]);
	}
}
