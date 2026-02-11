reset()
{
	free(data);
	if (graphused)
		free(realgraphdata);


	if (refcount > 0)
	{
		--refcount;
#if DGDEBUG
		std::cout << "de-reffing " << sourcefile << " due to manual list reset, refcount: " << refcount << std::endl;
#endif
		for (size_t i = 0; i < morelists.size(); ++i)
			o.lm.deRefList(morelists[i]);
	}
	data = NULL;
	realgraphdata = NULL;
	maxchildnodes = 0;
	graphitems = 0;
	data_length = 0;
	data_memory = 0;
	items = 0;
	isSW = false;
	issorted = false;
	graphused = false;
	force_quick_search = 0;


	category = "";
	istimelimited = false;
	combilist.clear();
	slowgraph.clear();
	list.clear();
	lengthlist.clear();
	weight.clear();
	itemtype.clear();
	timelimitindex.clear();
	morelists.clear();
	timelimits.clear();
	listcategory.clear();
	categoryindex.clear();
	used = false;
	parent = false;
	bannedpfile = "";
	exceptionpfile = "";
	weightedpfile = "";
	bannedpfiledate = 0;
	exceptionpfiledate = 0;
	weightedpfiledate = 0;
}
