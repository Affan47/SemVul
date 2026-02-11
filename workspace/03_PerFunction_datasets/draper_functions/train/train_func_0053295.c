listSamplerFactories()
{
    vector<pair<string, bool> > ans;
    list<pair<SamplerFactory*, bool> > const &flist = Model::samplerFactories();
    for (list<pair<SamplerFactory*, bool> >::const_iterator p = flist.begin();
	 p != flist.end(); ++p)
    {
	ans.push_back(pair<string,bool>(p->first->name(), p->second));
    }
    return ans;
}
